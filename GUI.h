//
// Created by CRISTIAN on 27/09/2026.
//

#ifndef PRACTICA_1_GUI_H
#define PRACTICA_1_GUI_H

#include "vector"
#include "string"

struct GLFWwindow;

namespace PAG{

    class GUI{
    private:
        static GUI* instacia;
        GUI();

        float colorGUI[3] = {0.0f,0.0f,0.0f};

        std::vector<std::string> mensajes;

        char nombreShader[128] = "pag03";
        int movimientoActual = 0;

    public:
        virtual ~GUI();
        static GUI& getInstancia();

        void inicializar(GLFWwindow *window);
        void nuevoFrame();
        void renderizarControles();
        void dibujar();
        void finalizar();

        void anadirMensaje(const std::string& msg);
        bool capturaRaton();
        bool capturaTeclado();

        int getMovimientoActual() const { return movimientoActual; }
    };


}


#endif //PRACTICA_1_GUI_H
