//
// Created by CRISTIAN on 05/10/2026.
//

#ifndef PRACTICA_1_SHADER_H
#define PRACTICA_1_SHADER_H


#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

namespace PAG {
    class Shader {
    private:
        GLuint idVS = 0;
        GLuint idFS = 0;
        GLuint idSP = 0;

    public:
        Shader();
        ~Shader();

        void compilarYEnlazar(const std::string &nombreComun);
        void activar() const;
        void setMat4(const std::string &nombre, const glm::mat4 &mat) const;
    };
}

#endif //PRACTICA_1_SHADER_H
