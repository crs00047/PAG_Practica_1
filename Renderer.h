//
// Created by CRISTIAN on 26/09/2026.
//
#include <glad/glad.h>

#ifndef PRACTICA_1_RENDERER_H
#define PRACTICA_1_RENDERER_H

//espacio de nombres para PAG::
namespace PAG {

    class Renderer {

    private:
        static Renderer* instancia;
        Renderer();

        float colorFondo[4] = {0.6f,0.6f,0.6f,1.0f};

    public:

        virtual ~Renderer();

        static Renderer& getInstancia();

        void inicializarOpenGL();
        void window_refresh();
        void framebuffer_size(int width, int height);
        void setColorFondo(float r, float g, float b, float a);
        const float* getColorFondo() const;

    };

}




#endif //PRACTICA_1_RENDERER_H
