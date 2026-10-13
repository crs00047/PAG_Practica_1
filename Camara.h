//
// Created by CRISTIAN on 14/10/2026.
//

#ifndef PRACTICA_1_CAMARA_H
#define PRACTICA_1_CAMARA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PAG {
    enum class MovimientoCamara { PAN, TILT, DOLLY, CRANE, ORBIT, ZOOM };

    class Camara {
    private:
        glm::vec3 posicion;
        glm::vec3 lookAt;
        glm::vec3 up;
        float fovy;
        float aspect;
        float zNear;
        float zFar;

    public:
        Camara();
        void setAspect(float a);
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
        void procesarMovimiento(MovimientoCamara mov, float dx, float dy);
    };
}


#endif //PRACTICA_1_CAMARA_H
