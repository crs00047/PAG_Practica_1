#version 410
layout (location = 0) in vec3 posicion;

// Variables uniform para recibir las matrices desde clase Renderer
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out datosVS {
    vec3 posicionLocal;
} salida;

void main ()
{
gl_Position = projection * view * model * vec4 ( posicion, 1.0 );
    salida.posicionLocal = posicion;
}