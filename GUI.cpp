//
// Created by CRISTIAN on 27/09/2026.
//

#include "GUI.h"
#include "Renderer.h"
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
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