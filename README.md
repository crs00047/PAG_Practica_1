# Practica 1
## Ejercicio 1  Cambiar color del fondo de ventana con la rueda del ratón
### Solución

He aprovechado la función ya implementada scroll_callback como base de nuestra solución. 
Para empezar, usamos un función de OpenGL para obtener el valor actual indicando en su modificador  sea del color del fondo de pantalla (GL_COLOR_CLEAR_VALUE) y se le pasa al vector color. Teniendo en cuenta que solo se puede usar la rueda del ratón he preferido que el cambio del color sea uniforme con un valor de 0.05 por cada giro de la rueda, haciendo solo se muestre un cambio de negro a blanco o viceversa. 

Una vez que tenemos el color del fondo tomamos el movimiento del raton y se le multiplica por cada giro detectado. Antes de refrescar la pantalla se comprueba que el rango de color y opacidad esté entre 0 y 1. 
En el caso de que sea menor a 0, que siga siendo 0. 
En el caso de que sea mayor a 1, se divide el mayor valor entre todos los valores de color tal y como se vió en la teoria del tema 1 para bajar la proporción del color igual para todos. 

Por ultimo se aplica con un **glClearColor** y refrescamos la pantalla con la función **window_refresh_callback** pasandole la ventana creada en el main.