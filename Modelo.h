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


struct Material {
    glm::vec3 colorAmbiente = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 colorDifuso = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 colorEspecular = glm::vec3(1.0f, 1.0f, 1.0f);
    float exponenteEspecular = 32.0f;
};

enum class ModoVisualizacion {
    ALAMBRE,
    SOLIDO
};


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

        Material material;

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
        void cargarDesdeOBJ(const std::string& rutaArchivo);

        Material& getMaterial() { return material; }
    };
}

#endif //PRACTICA_1_MODELO_H
