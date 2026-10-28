#version 410
layout (location = 0) in vec3 posicion;

// Variables uniform para recibir las matrices desde tu clase Renderer
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 colorMalla;

void main ()
{
    // Multiplicación en el orden correcto: Proyección * Vista * Modelo (Posición)
    gl_Position = projection * view * model * vec4 ( posicion, 1.0 );
    colorMalla = abs(normalize(posicion));
}