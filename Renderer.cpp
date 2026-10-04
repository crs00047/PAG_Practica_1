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
        if (idVS != 0){
            glDeleteShader(idVS);
        }

        if (idFS != 0){
            glDeleteShader(idFS);
        }

        if (idSP != 0){
            glDeleteProgram(idSP);
        }

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
        glUseProgram(idSP);
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
* Método para crear, compilar y enlazar el shader program
* @note No se incluye ninguna comprobación de errores
*/
    void PAG::Renderer::creaShaderProgram(const std::string &nombreComun)
    {

        std::string rutaVS = nombreComun + "-vs.glsl";
        std::string rutaFS = nombreComun + "-fs.glsl";


        // Carga del Vertex Shader desde archivo
        std::ifstream archivoVS(rutaVS);
        if (!archivoVS.is_open()) {
            throw std::runtime_error("Error: No se pudo abrir el archivo " + rutaVS);
        }
        std::stringstream streamVS;
        streamVS << archivoVS.rdbuf();
        std::string miVertexShader = streamVS.str();
        archivoVS.close();

        // Carga del Fragment Shader desde archivo
        std::ifstream archivoFS(rutaFS);
        if (!archivoFS.is_open()) {
            throw std::runtime_error("Error: No se pudo abrir el archivo " + rutaFS);
        }
        std::stringstream streamFS;
        streamFS << archivoFS.rdbuf();
        std::string miFragmentShader = streamFS.str();
        archivoFS.close();

        idVS = glCreateShader ( GL_VERTEX_SHADER );

        // VERTEX SHADER
        if (idVS == 0){
            throw std::runtime_error("Error: No se pudo crear el objeto Vertex Array Shader");
        }

        const GLchar* fuenteVS = miVertexShader.c_str ();
        glShaderSource ( idVS, 1, &fuenteVS, nullptr );
        glCompileShader ( idVS );

        GLint resultadoCompilacionVS;
        glGetShaderiv(idVS, GL_COMPILE_STATUS, &resultadoCompilacionVS);
        if (resultadoCompilacionVS == GL_FALSE){
            GLint  tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(idVS, GL_INFO_LOG_LENGTH, &tamMsj);
            if (tamMsj > 0){
                GLchar* mensajeFormatoC = new GLchar;
                GLint datosEscritos = 0;
                glGetShaderInfoLog(idVS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
            }
            throw std::runtime_error("Error de compilación en Vertex Shader: \n" + mensaje);
        }

        //FRAGMENT SHADER
        idFS = glCreateShader ( GL_FRAGMENT_SHADER );
        if (idFS == 0){
            throw std::runtime_error("Error: No se pudo crear el objeto Fragment Shader.");
        }
        const GLchar* fuenteFS = miFragmentShader.c_str ();
        glShaderSource ( idFS, 1, &fuenteFS, nullptr );
        glCompileShader ( idFS );

        GLint resultadoCompilacionFS;
        glGetShaderiv(idFS, GL_COMPILE_STATUS, &resultadoCompilacionFS);
        if (resultadoCompilacionFS == GL_FALSE){
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(idFS, GL_INFO_LOG_LENGTH, &tamMsj);
            if (tamMsj > 0){
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog(idFS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
            }
            throw std::runtime_error("Error de compilacion en Fragment Shader:\n" + mensaje);
        }

        // SHADER PROGRAM
        idSP = glCreateProgram ();
        if (idSP == 0){
            throw std::runtime_error("Error: No se pudo crear el objeto Shader Program");
        }
        glAttachShader ( idSP, idVS );
        glAttachShader ( idSP, idFS );
        glLinkProgram ( idSP );

        GLint resultadoEnlazado = 0;
        glGetProgramiv(idSP, GL_LINK_STATUS, &resultadoEnlazado);
        if (resultadoEnlazado == GL_FALSE){
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv(idSP, GL_INFO_LOG_LENGTH, &tamMsj);
            if (tamMsj > 0){
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog(idSP, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
            }
            throw std::runtime_error("Error de enlazado en el Shader Program:\n" + mensaje);
        }
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

