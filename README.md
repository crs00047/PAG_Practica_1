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


# Práctica 4 y 5
## Solución

Desacoplamos la gestión de los shaders de la clase Renderer creando la nueva clase `Shader`.
La clase `Shader` encapsulamos la lectura de los ficheros (`-vs.glsl` y `-fs.glsl`), la compilación con comprobación de errores y el enlazado del Shader Program.
Por último, añadimos a la interfaz de ImGui una nueva ventana llamada "Shader Program", que cuenta con un campo de texto (`InputText`) para especificar el nombre base del shader y un botón "Load" para cargarlo y enlazarlo dinámicamente en tiempo de ejecución.

Para la práctica 5, creamos la clase `Camara` junto a un enum `MovimientoCamara` para modelar la cámara a partir de sus parámetros básicos.
Con ellos calculamos las matrices de transformación de vista y proyección mediante `glm::lookAt` y `glm::perspective`.
En la clase `Renderer` pasamos en cada frame las matrices calculadas de vista y proyección al shader activo mediante uniforms, pero se adapta el Vertex Shader para recibir estas matrices y transformar
Por último, en la interfaz ImGui creamos la ventana "Camera" con un menú desplegable (`Combo`) para seleccionar el movimiento activo. Registrando todos los movimientos en el main con un callback `glfwSetCursorPosCallback`.



# Práctica 6
## Solución

En el primer commit, se desacopla la gestión de los shaders de la clase Renderer creando la nueva clase `Modelo` y probarla en el main.

Durante el segundo commit, intenté cargar los modelos obj con assimp pero daba errores que mirando por internet y consultando a la IA indicaban que eran problemas con
los archivos .dll tal y como se mencionó en clase, intenté solucionarlo pero no se arreglaba, por lo que al final opté por una de las alternativas del guión `Tinyobjloader`.

Durante el tercer commit se hace el resto del guion, como cambiar la interfaz para la carga de los modelos siendo posible varios, poder aplicar las transformaciones al modelo que solo se aplican al darle al botón ,
corregir un error de la cámara cuando el ángulo llegaba a 90, escribir el diagrama UML en el readme.md en vez de en el archivo UML.puml como en la anterior práctica y por último redactar en este archivo que se ha hecho durante la práctica.


## Diagrama UML

```
@startuml
class Renderer {
    - {static} instancia : Renderer*
    - colorFondo : float[4]
    - modelos : std::vector<Modelo*>
    - shader : Shader*
    - camara : Camara
    + {static} getInstancia() : Renderer
    + inicializarOpenGL() : void
    + window_refresh() : void
    + framebuffer_size(width: int, height: int) : void
    + cargarShader(nombreComun: string) : void
    + anadirModelo(m: Modelo*) : void
    + eliminarModelo(index: int) : void
    + getModelos() : std::vector<Modelo*>
}

class Modelo {
    - idVAO : GLuint
    - idVBO : GLuint
    - idIBO : GLuint
    - numIndices : int
    - posicion : glm::vec3
    - rotacion : glm::vec3
    - escala : glm::vec3
    + cargarDesdeOBJ(ruta: string) : void
    + dibujar(shader: Shader*) : void
    + getMatrizModelado() : mat4
    + setPosicion(p: vec3) : void
    + setRotacion(r: vec3) : void
    + setEscala(e: vec3) : void
}

class GUI {
    - {static} instancia : GUI*
    - mensajes : std::vector<string>
    - modeloSeleccionado : int
    - inputPosicion : float[3]
    - inputRotacion : float[3]
    - inputEscala : float[3]
    + {static} getInstancia() : GUI
    + renderizarControles() : void
    + anadirMensaje(msg: string) : void
}

class Camara {
    - posicion : glm::vec3
    - lookAt : glm::vec3
    - fov : float
    + getViewMatrix() : mat4
    + getProjectionMatrix() : mat4
    + procesarMovimiento(mov: MovimientoCamara, dx: float, dy: float) : void
}

class Shader {
    - idVS : GLuint
    - idFS : GLuint
    - idSP : GLuint
    + compilarYEnlazar(nombre: string) : void
    + activar() : void
    + setMat4(nombre: string, mat: mat4) : void
}

Renderer "1" *-- "0..*" Modelo : contiene
Renderer "1" *-- "1" Shader : usa
Renderer "1" *-- "1" Camara : usa
GUI ..> Renderer : interactúa
@enduml