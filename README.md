# Practica 2

## Solución

Para el primer commit he creado la clase renderer usando el patrón Singleton,
además durante esté commit probé en el main el código para ImGUI.

Durante el segundo main desacoplé del main la parte de OpenGL implementando todas las funciones como el refresco de ventana llamado **window_refresh** en la clase Renderer o quitar el vector colorFondo como variable de función y pasarla como variable en la clase Renderer.

En los commits de la creación de la clase GUI y la corrección utilizo el código que probé en el main y lo implemento completamente
en la clase GUI, por otro lado también implemento los controles para teclado y ratón junto a las ventanas de la interfaz para mensajes de la consola. Por ejemplo, el cambio del color del fondo que en el primer commit antes de la corrección
no se actualizaba los valores de R,G,B si se hacía con el ratón, solo se actualizaba con el uso de la ventana.


# Practica 3

## Solución

Para empezar comprobamos que el código del pdf funciona correctamente en el main.

Como segundo commit se implementa el código del manejo de excepciones en la compilación como en el enlazada del shader
con la función **glGetShaderiv** para conocer por parte de OpenGL el estado y luego glGetShaderInfoLog para obtener el error concreto.

En el último (tercero) pasamos el texto que teniamos una variable tanto del vertex shader como del fragment shader usando un formato de nombre-tipo.glsl con una lectura
por parte de stringstream, se convierte a c_str y por ultimo se compila. Por otro lado también corregí el manejo de excepciones en el main al no tener ningún catch o try.

Respecto al comportamiento del triágulo, es probable en base a lo que se ha visto
en teoría que se deba al reajuste de la pantalla haciendo que el triágulo se adapte constantemente al tamaño actual de pantalla
ya que no reajustamos su ubicación de los vértices en pantalla