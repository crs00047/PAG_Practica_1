#version 410
in vec3 colorMalla;
out vec4 colorFragmento;
void main ()
{ colorFragmento = vec4 ( colorMalla, 1.0 );
}