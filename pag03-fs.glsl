#version 410


// Bloque de interfaz de entrada (debe coincidir el nombre 'datosVS')
in datosVS {
    vec3 posicionLocal;
} entrada;

out vec4 colorFragmento;

// 1. Definición del tipo de la subrutina
subroutine vec4 fCalcularColor();

// 2. Uniform asociado a la subrutina
subroutine uniform fCalcularColor uMetodoColorElegido;

// 3. Implementaciones de la subrutina
subroutine (fCalcularColor)
vec4 colorAlambre() {
    return vec4(1.0, 0.2, 0.2, 1.0);
}

subroutine (fCalcularColor)
vec4 colorSolido() {
    return vec4(colorDifuso, 1.0);
}

void main ()
{
    colorFragmento = uMetodoColorElegido();
}