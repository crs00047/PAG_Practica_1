//
// Created by CRISTIAN on 27/10/2026.
//

#ifndef PRACTICA_1_MODELO_H
#define PRACTICA_1_MODELO_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "Shader.h"

namespace PAG {
    class Modelo {
    private:
        GLuint idVAO = 0;
        GLuint idVBO = 0;
        GLuint idIBO = 0;
        GLuint numIndices = 0;

        glm::vec3 posicion;
        glm::vec3 rotacion;
        glm::vec3 escala;

    public:
        std::string nombre;

        Modelo(const std::string& nombre = "Modelo");
        ~Modelo();

        // Transformaciones
        void setPosicion(const glm::vec3& p) { posicion = p; }
        void setRotacion(const glm::vec3& r) { rotacion = r; }
        void setEscala(const glm::vec3& e) { escala = e; }

        glm::vec3 getPosicion() const { return posicion; }
        glm::vec3 getRotacion() const { return rotacion; }
        glm::vec3 getEscala() const { return escala; }

        glm::mat4 getMatrizModelado() const;

        void crearTrianguloPrueba();
        void dibujar(Shader* shader);
    };
}

#endif //PRACTICA_1_MODELO_H
