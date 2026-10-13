//
// Created by CRISTIAN on 26/09/2026.
//

#include "Renderer.h"
#include "iostream"
#include "fstream"
#include "sstream"

namespace PAG {

    Renderer* Renderer::instancia = nullptr;

    Renderer::Renderer() {}

    Renderer::~Renderer() {

        if (idVBO != 0){
            glDeleteBuffers(1, &idVBO);
        }

        if (idIBO != 0){
            glDeleteBuffers(1, &idIBO);
        }

        if (idVAO != 0){
            glDeleteVertexArrays(1, &idVAO);
        }
        
    }

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
        glBindVertexArray(idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
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




    /**
* Método para crear el VAO para el modelo a renderizar
* @note No se incluye ninguna comprobación de errores
*/
    void PAG::Renderer::creaModelo ( )
    { GLfloat vertices[] = { -.5, -.5, 0,
                             .5, -.5, 0,
                             .0, .5, 0 };
        GLuint indices[] = { 0, 1, 2 };
        glGenVertexArrays ( 1, &idVAO );
        glBindVertexArray ( idVAO );
        glGenBuffers ( 1, &idVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, idVBO );
        glBufferData ( GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW );
        glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr );
        glEnableVertexAttribArray ( 0 );
        glGenBuffers ( 1, &idIBO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLuint), indices, GL_STATIC_DRAW );
    }




}

