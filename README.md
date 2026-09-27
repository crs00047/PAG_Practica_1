# Practica 2

## Solución

Para el primer commit he creado la clase renderer usando el patrón Singleton,
además durante esté commit probé en el main el código para ImGUI.

Durante el segundo main desacoplé del main la parte de OpenGL implementando todas las funciones como el refresco de ventana llamado **window_refresh** en la clase Renderer o quitar el vector colorFondo como variable de función y pasarla como variable en la clase Renderer.

En los commits de la creación de la clase GUI y la corrección utilizo el código que probé en el main y lo implemento completamente
en la clase GUI, por otro lado también implemento los controles para teclado y ratón junto a las ventanas de la interfaz para mensajes de la consola. Por ejemplo, el cambio del color del fondo que en el primer commit antes de la corrección
no se actualizaba los valores de R,G,B si se hacía con el ratón, solo se actualizaba con el uso de la ventana.