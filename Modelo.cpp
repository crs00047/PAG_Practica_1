//
// Created by CRISTIAN on 27/10/2026.
//

#include "Modelo.h"

namespace PAG {
    Modelo::Modelo(const std::string& n) : nombre(n), posicion(0.0f), rotacion(0.0f), escala(1.0f) {}

    Modelo::~Modelo() {
        if (idVBO != 0) glDeleteBuffers(1, &idVBO);
        if (idIBO != 0) glDeleteBuffers(1, &idIBO);
        if (idVAO != 0) glDeleteVertexArrays(1, &idVAO);
    }

    glm::mat4 Modelo::getMatrizModelado() const {
        glm::mat4 matriz(1.0f);
        matriz = glm::translate(matriz, posicion);
        matriz = glm::rotate(matriz, glm::radians(rotacion.x), glm::vec3(1, 0, 0));
        matriz = glm::rotate(matriz, glm::radians(rotacion.y), glm::vec3(0, 1, 0));
        matriz = glm::rotate(matriz, glm::radians(rotacion.z), glm::vec3(0, 0, 1));
        matriz = glm::scale(matriz, escala);
        return matriz;
    }

    void Modelo::crearTrianguloPrueba() {
        GLfloat vertices[] = { -.5, -.5, 0,  .5, -.5, 0,  .0, .5, 0 };
        GLuint indices[] = { 0, 1, 2 };
        numIndices = 3;

        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    void Modelo::dibujar(Shader* shader) {
        if (idVAO == 0 || shader == nullptr) return;

        shader->setMat4("model", getMatrizModelado());

        glBindVertexArray(idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}