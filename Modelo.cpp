//
// Created by CRISTIAN on 27/10/2026.
//

#include "Modelo.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <stdexcept>
#include <iostream>

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

    void Modelo::cargarDesdeOBJ(const std::string& rutaArchivo) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string err;

        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, rutaArchivo.c_str());

        if (!err.empty()) {
            std::cerr << "TinyObjLoader error: " << err << std::endl;
        }

        if (!ret) {
            throw std::runtime_error("Error al cargar el archivo OBJ: " + rutaArchivo);
        }

        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        GLuint indiceActual = 0;

        // Recorremos las mallas (shapes) que contenga el OBJ
        for (size_t s = 0; s < shapes.size(); s++) {
            // Recorremos los índices de los vértices
            for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[i];

                // Extraemos las coordenadas X, Y, Z del vértice
                vertices.push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 0]);
                vertices.push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 1]);
                vertices.push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 2]);

                // Generamos un índice secuencial para pintar el triángulo
                indices.push_back(indiceActual++);
            }
        }

        numIndices = indices.size();

        // Generación de Buffers de OpenGL (VBO, IBO, VAO)
        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

}