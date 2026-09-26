//
// Created by CRISTIAN on 26/09/2026.
//

#include "Renderer.h"
#include "iostream"


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
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::window_refresh() {
        glClearColor(colorFondo[0], colorFondo[1], colorFondo[2], colorFondo[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::framebuffer_size(int width, int height) {
        glViewport(0,0, width, height);
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

}

