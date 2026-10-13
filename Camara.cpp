//
// Created by CRISTIAN on 14/10/2026.
//

#include "Camara.h"
#include <glm/gtx/transform.hpp>

namespace PAG {

    Camara::Camara() : posicion(0.0f, 0.0f, 2.0f), lookAt(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f),
                       fovy(glm::radians(45.0f)), aspect(1.0f), zNear(0.1f), zFar(100.0f) {}

    void Camara::setAspect(float a) { aspect = a; }

    glm::mat4 Camara::getViewMatrix() const {
        return glm::lookAt(posicion, lookAt, up);
    }

    glm::mat4 Camara::getProjectionMatrix() const {
        return glm::perspective(fovy, aspect, zNear, zFar);
    }

    void Camara::procesarMovimiento(MovimientoCamara mov, float dx, float dy) {
        float sensibilidadRot = 0.01f;
        float sensibilidadTras = 0.02f;

        glm::vec3 direccion = lookAt - posicion;
        glm::vec3 w = glm::normalize(-direccion);
        glm::vec3 u = glm::normalize(glm::cross(up, w));
        glm::vec3 v = glm::cross(w, u);

        switch(mov) {
            case MovimientoCamara::PAN: {
                glm::mat4 rot = glm::rotate(-dx * sensibilidadRot, v);
                lookAt = posicion + glm::vec3(rot * glm::vec4(direccion, 0.0f));
                break;
            }
            case MovimientoCamara::TILT: {
                glm::mat4 rot = glm::rotate(-dy * sensibilidadRot, u);
                lookAt = posicion + glm::vec3(rot * glm::vec4(direccion, 0.0f));
                break;
            }
            case MovimientoCamara::DOLLY: {
                glm::vec3 traslacion = -w * (dy * sensibilidadTras) + u * (dx * sensibilidadTras);
                posicion += traslacion;
                lookAt += traslacion;
                break;
            }
            case MovimientoCamara::CRANE: {
                glm::vec3 traslacion = v * (-dy * sensibilidadTras);
                posicion += traslacion;
                lookAt += traslacion;
                break;
            }
            case MovimientoCamara::ORBIT: {
                glm::mat4 rotX = glm::rotate(-dx * sensibilidadRot, up);
                glm::mat4 rotY = glm::rotate(-dy * sensibilidadRot, u);
                glm::vec3 dist = posicion - lookAt;
                posicion = lookAt + glm::vec3(rotX * rotY * glm::vec4(dist, 1.0f));
                break;
            }
            case MovimientoCamara::ZOOM: {
                fovy += dy * sensibilidadRot;
                if (fovy < 0.1f) fovy = 0.1f;
                if (fovy > glm::radians(150.0f)) fovy = glm::radians(150.0f);
                break;
            }
        }
    }
}