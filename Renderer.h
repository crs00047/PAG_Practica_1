//
// Created by CRISTIAN on 26/09/2026.
//
#include "glad/glad.h"
#include <string>

#ifndef PRACTICA_1_RENDERER_H
#define PRACTICA_1_RENDERER_H

#include "Shader.h"
#include "Camara.h"

//espacio de nombres para PAG::
namespace PAG {

    class Renderer {

    private:
        static Renderer* instancia;
        Renderer();

        float colorFondo[4] = {0.6f,0.6f,0.6f,1.0f};

        // Atributos para los identificadores de la geometría y los shaders

        GLuint idVAO = 0; //Identificador del vertex array object
        GLuint idVBO = 0; //Identificador del vertex buffer object
        GLuint idIBO = 0; //Identificador del index buffer object

        Shader* shader = nullptr;
        Camara camara;

    public:

        virtual ~Renderer();

        static Renderer& getInstancia();

        void inicializarOpenGL();
        void window_refresh();
        void framebuffer_size(int width, int height);
        void setColorFondo(float r, float g, float b, float a);
        const float* getColorFondo() const;

        void cargarShader(const std::string &nombreComun);
        void creaModelo();

        void moverCamara(float dx, float dy);
        void setMovimientoCamara(int tipoMovimiento);


    };

}




#endif //PRACTICA_1_RENDERER_H
