//
// Created by CRISTIAN on 05/10/2026.
//

#include "Shader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

namespace PAG {

    Shader::Shader() {}

    Shader::~Shader() {
        if (idVS != 0) glDeleteShader(idVS);
        if (idFS != 0) glDeleteShader(idFS);
        if (idSP != 0) glDeleteProgram(idSP);
    }

    void Shader::compilarYEnlazar(const std::string &nombreComun) {
        std::string rutaVS = nombreComun + "-vs.glsl";
        std::string rutaFS = nombreComun + "-fs.glsl";

        std::ifstream archivoVS(rutaVS);
        if (!archivoVS.is_open()) {
            throw std::runtime_error("Error: No se pudo abrir el archivo " + rutaVS);
        }
        std::stringstream streamVS;
        streamVS << archivoVS.rdbuf();
        std::string miVertexShader = streamVS.str();
        archivoVS.close();

        std::ifstream archivoFS(rutaFS);
        if (!archivoFS.is_open()) {
            throw std::runtime_error("Error: No se pudo abrir el archivo " + rutaFS);
        }
        std::stringstream streamFS;
        streamFS << archivoFS.rdbuf();
        std::string miFragmentShader = streamFS.str();
        archivoFS.close();

        idVS = glCreateShader(GL_VERTEX_SHADER);
        if (idVS == 0) throw std::runtime_error("Error: No se pudo crear el Vertex Shader");

        const GLchar* fuenteVS = miVertexShader.c_str();
        glShaderSource(idVS, 1, &fuenteVS, nullptr);
        glCompileShader(idVS);

        GLint resultadoCompilacionVS;
        glGetShaderiv(idVS, GL_COMPILE_STATUS, &resultadoCompilacionVS);
        if (resultadoCompilacionVS == GL_FALSE) {
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(idVS, GL_INFO_LOG_LENGTH, &tamMsj);
            if (tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog(idVS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
            }
            throw std::runtime_error("Error de compilación en Vertex Shader: \n" + mensaje);
        }

        idFS = glCreateShader(GL_FRAGMENT_SHADER);
        if (idFS == 0) throw std::runtime_error("Error: No se pudo crear el Fragment Shader");

        const GLchar* fuenteFS = miFragmentShader.c_str();
        glShaderSource(idFS, 1, &fuenteFS, nullptr);
        glCompileShader(idFS);

        GLint resultadoCompilacionFS;
        glGetShaderiv(idFS, GL_COMPILE_STATUS, &resultadoCompilacionFS);
        if (resultadoCompilacionFS == GL_FALSE) {
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(idFS, GL_INFO_LOG_LENGTH, &tamMsj);
            if (tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog(idFS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
            }
            throw std::runtime_error("Error de compilación en Fragment Shader:\n" + mensaje);
        }

        idSP = glCreateProgram();
        if (idSP == 0) throw std::runtime_error("Error: No se pudo crear el Shader Program");

        glAttachShader(idSP, idVS);
        glAttachShader(idSP, idFS);
        glLinkProgram(idSP);

        GLint resultadoEnlazado = 0;
        glGetProgramiv(idSP, GL_LINK_STATUS, &resultadoEnlazado);
        if (resultadoEnlazado == GL_FALSE) {
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv(idSP, GL_INFO_LOG_LENGTH, &tamMsj);
            if (tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog(idSP, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
            }
            throw std::runtime_error("Error de enlazado en el Shader Program:\n" + mensaje);
        }
    }

    void Shader::activar() const {
        if (idSP != 0) glUseProgram(idSP);
    }

    void Shader::setMat4(const std::string &nombre, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(idSP, nombre.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }
}