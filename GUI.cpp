//
// Created by CRISTIAN on 27/09/2026.
//

#include "GUI.h"
#include "Renderer.h"
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdexcept>
#include <cstdlib>

namespace PAG {

    GUI* GUI::instacia = nullptr;

    GUI::GUI() {}

    GUI::~GUI() {}

    GUI& GUI::getInstancia() {
        if (!instacia){
            instacia = new GUI();
        }
        return *instacia;
    }


    void GUI::inicializar(GLFWwindow *window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }


    void GUI::nuevoFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }


    void GUI::renderizarControles() {
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_Once);
        if (ImGui::Begin("Mensajes")){
            ImGui::SetWindowFontScale(1.0f);

            for (const std::string& msg : mensajes) {
                ImGui::Text("%s", msg.c_str());
            }

            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }
            
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(370,10), ImGuiCond_Once);
        if (ImGui::Begin("Escena")) {
            ImGui::SetWindowFontScale(1.0f);

            const float* colorActual = PAG::Renderer::getInstancia().getColorFondo();
            colorGUI[0] = colorActual[0];
            colorGUI[1] = colorActual[1];
            colorGUI[2] = colorActual[2];

            if (ImGui::ColorEdit3("Color de fondo", colorGUI)) {
                PAG::Renderer::getInstancia().setColorFondo(colorGUI[0], colorGUI[1], colorGUI[2], 1.0f);
            }
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(740, 10), ImGuiCond_Once);
        if (ImGui::Begin("Shader Program")) {
            ImGui::InputText("##ShaderName", nombreShader, sizeof(nombreShader), ImGuiInputTextFlags_AutoSelectAll);            if (ImGui::Button("Load")) {
                try {
                    PAG::Renderer::getInstancia().cargarShader(nombreShader);
                    anadirMensaje("Shader program " + std::string(nombreShader) + " cargado.");
                } catch (const std::runtime_error& e) {
                    anadirMensaje(e.what());
                }
            }
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(370, 150), ImGuiCond_Once);
        if (ImGui::Begin("Camera")) {
            const char* movimientos[] = { "Pan", "Tilt", "Dolly", "Crane", "Orbit", "Zoom" };
            ImGui::Combo("Movement", &movimientoActual, movimientos, 6);
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(10, 220), ImGuiCond_Once);
        if (ImGui::Begin("Gestión de Modelos")) { //[cite: 5]
            ImGui::InputText("Ruta OBJ", rutaModelo, IM_ARRAYSIZE(rutaModelo));

            if (ImGui::Button("Cargar OBJ")) {
                PAG::Modelo* m = nullptr;
                try {
                    m = new PAG::Modelo("Modelo " + std::to_string(PAG::Renderer::getInstancia().getModelos().size() + 1));
                    m->cargarDesdeOBJ(rutaModelo);

                    float rX = ((rand() % 100) / 50.0f) - 1.0f;
                    float rZ = ((rand() % 100) / 50.0f) - 1.0f;
                    m->setPosicion(glm::vec3(rX, 0.0f, rZ));

                    PAG::Renderer::getInstancia().anadirModelo(m);
                    anadirMensaje("Modelo cargado exitosamente.");
                } catch (const std::exception& e) {
                    anadirMensaje(e.what());
                    if (m != nullptr) {
                        delete m;
                    }
                }
            }

            ImGui::Separator();
            ImGui::Text("Modelos en escena:");

            auto& modelos = PAG::Renderer::getInstancia().getModelos();
            for (int i = 0; i < modelos.size(); i++) {
                if (ImGui::Selectable(modelos[i]->nombre.c_str(), modeloSeleccionado == i)) {
                    modeloSeleccionado = i;

                    glm::vec3 p = modelos[i]->getPosicion();
                    glm::vec3 r = modelos[i]->getRotacion();
                    glm::vec3 e = modelos[i]->getEscala();

                    inputPosicion[0] = p.x; inputPosicion[1] = p.y; inputPosicion[2] = p.z;
                    inputRotacion[0] = r.x; inputRotacion[1] = r.y; inputRotacion[2] = r.z;
                    inputEscala[0] = e.x;   inputEscala[1] = e.y;   inputEscala[2] = e.z;
                }
            }

            if (modeloSeleccionado >= 0 && modeloSeleccionado < modelos.size()) {
                if (ImGui::Button("Eliminar Seleccionado")) { //[cite: 5]
                    PAG::Renderer::getInstancia().eliminarModelo(modeloSeleccionado);
                    modeloSeleccionado = -1;
                }
            }
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(10, 450), ImGuiCond_Once);
        if (ImGui::Begin("Transformaciones")) {
            auto& modelos = PAG::Renderer::getInstancia().getModelos();
            if (modeloSeleccionado >= 0 && modeloSeleccionado < modelos.size()) {
                PAG::Modelo* m = modelos[modeloSeleccionado];

                ImGui::InputFloat3("Posición", inputPosicion);
                ImGui::InputFloat3("Rotación", inputRotacion);
                ImGui::InputFloat3("Escala", inputEscala);

                if (ImGui::Button("Aplicar Transformación")) {
                    m->setPosicion(glm::vec3(inputPosicion[0], inputPosicion[1], inputPosicion[2]));
                    m->setRotacion(glm::vec3(inputRotacion[0], inputRotacion[1], inputRotacion[2]));
                    m->setEscala(glm::vec3(inputEscala[0], inputEscala[1], inputEscala[2]));

                    anadirMensaje("Transformaciones aplicadas a " + m->nombre);
                }
            } else {
                ImGui::Text("Selecciona un modelo primero.");
            }
        }
        ImGui::End();


    }

    void GUI::dibujar() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GUI::finalizar() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GUI::anadirMensaje(const std::string &msg) {
        mensajes.push_back(msg);
    }

    bool GUI::capturaRaton() {
        return ImGui::GetIO().WantCaptureMouse;
    }

    bool GUI::capturaTeclado() {
        return ImGui::GetIO().WantCaptureKeyboard;
    }
}