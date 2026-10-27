//
// Created by CRISTIAN on 26/09/2026.
//

#include "Renderer.h"
#include "GUI.h"
#include "iostream"
#include "fstream"
#include "sstream"

namespace PAG {

    Renderer* Renderer::instancia = nullptr;

    Renderer::Renderer() {}

    Renderer::~Renderer() {}

    Renderer& Renderer::getInstancia() {
        if (!instancia){
            instancia = new Renderer();
        }
        return *instancia;
    }

    void Renderer::inicializarOpenGL() {
        //Reutilizacion de la funcion para el código de la práctica 3
        glClearColor(colorFondo[0], colorFondo[1], colorFondo[2], colorFondo[3]);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
    }

    void Renderer::window_refresh() {
        //Reutilización de la función para el
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(colorFondo[0], colorFondo[1], colorFondo[2], colorFondo[3]);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (shader != nullptr) {
            shader->activar();
            shader->setMat4("view", camara.getViewMatrix());
            shader->setMat4("projection", camara.getProjectionMatrix());

            for (Modelo* modelo : modelos) {
                modelo->dibujar(shader);
            }
        }
    }

    void Renderer::framebuffer_size(int width, int height) {
        glViewport(0,0, width, height);
        if (height > 0) camara.setAspect((float)width / (float)height);
    }

    void Renderer::setColorFondo(float r, float g, float b, float a) {
        colorFondo[0] = r;
        colorFondo[1] = g;
        colorFondo[2] = b;
        colorFondo[3] = a;
    }

    const float* Renderer::getColorFondo() const {
        return colorFondo;
    }


    void Renderer::cargarShader(const std::string &nombreComun) {
        Shader* nuevoShader = new Shader();
        nuevoShader->compilarYEnlazar(nombreComun);

        if (shader != nullptr) delete shader;
        shader = nuevoShader;
    }

    void Renderer::moverCamara(float dx, float dy) {
        MovimientoCamara mov = static_cast<MovimientoCamara>(GUI::getInstancia().getMovimientoActual());
        camara.procesarMovimiento(mov, dx, dy);
    }


    void Renderer::eliminarModelo(int index) {
        if (index >= 0 && index < modelos.size()) {
            delete modelos[index];
            modelos.erase(modelos.begin() + index);
        }
    }

}

