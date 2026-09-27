#include <iostream>
// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include "Renderer.h"
#include "GUI.h"

// - Esta función callback será llamada cuando GLFW produzca algún error
void error_callback ( int errno, const char* desc )
{ std::string aux (desc);
    PAG::GUI::getInstancia().añadirMensaje("Error de GLFW número " + std::to_string(errno) + ": " + aux);
}
// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback ( GLFWwindow *window )
{
    // glClear con windows_refresh de Renderer
    PAG::Renderer::getInstancia().window_refresh();

// - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
// intercambia el buffer back (que se ha estado dibujando) por el
// que se mostraba hasta ahora front. Debe ser la última orden de
// este callback
    glfwSwapBuffers ( window );
    std::cout << "Refresh callback called" << std::endl;
    PAG::GUI::getInstancia().añadirMensaje("Refresh callback called");
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback ( GLFWwindow *window, int width, int height )
{
    //Viewport con Renderer
    PAG::Renderer::getInstancia().framebuffer_size(width, height);

    PAG::GUI::getInstancia().añadirMensaje("Resize callback called: " + std::to_string(width) + "x" + std::to_string(height));}
// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods )
{ if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    { glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    PAG::GUI::getInstancia().añadirMensaje("Key callback called");}
// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods )
{
    if (PAG::GUI::getInstancia().capturaRaton()) return;

    if ( action == GLFW_PRESS ) {
        PAG::GUI::getInstancia().añadirMensaje("Pulsado el botón: " + std::to_string(button));
    } else if ( action == GLFW_RELEASE ) {
        PAG::GUI::getInstancia().añadirMensaje("Soltado el botón: " + std::to_string(button));
    }
}
// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset )
{

    if (PAG::GUI::getInstancia().capturaRaton()) return;

    PAG::GUI::getInstancia().añadirMensaje("Rueda movida: " + std::to_string(xoffset) + ", " + std::to_string(yoffset));

    //  Vector de tamaño 4 para el R,G,B,A (opacidad)
    const float* colorActual = PAG::Renderer::getInstancia().getColorFondo();

    // Cuanto cambiar con cada tick de raton
    float raton = 0.05f;

    //Copia para modificar
    float color[4] = { colorActual[0], colorActual[1], colorActual[2], colorActual[3] };

    //RGB

    color[0] += (float)yoffset * raton;
    color[1] += (float)yoffset * raton;
    color[2] += (float)yoffset * raton;

    // Opacidad
    color[3] += (float)xoffset * raton;

    // Limite de color por debajo de 0

    if (color[0] < 0.0f) color[0] = 0.0f;
    if (color[1] < 0.0f) color[1] = 0.0f;
    if (color[2] < 0.0f) color[2] = 0.0f;

    //Limite de color por encima de 1

    //Buscar el mayor
    float maxColor = color[0];
    if (color[1] > maxColor) maxColor = color[1];
    if (color[2] > maxColor) maxColor = color[2];

    //Bajar los demas respecto al mayor
    if (maxColor > 1.0f) {
        color[0] = color[0] / maxColor;
        color[1] = color[1] / maxColor;
        color[2] = color[2] / maxColor;
    }

    // Limitar A
    if (color[3] > 1.0f) color[3] = 1.0f;
    if (color[3] < 0.0f) color[3] = 0.0f;

    PAG::Renderer::getInstancia().setColorFondo(color[0], color[1], color[2], color[3]);
}


int main()
{ std::cout << "Starting Application PAG - Prueba 01" << std::endl;



    // - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) error_callback );

    // - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if ( glfwInit () != GLFW_TRUE )
    { std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }


    // - Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    // modo Core Profile.
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // - Esta y las 2
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 ); // siguientes activan un contexto
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 3 ); // OpenGL Core Profile 4.3.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    // la creamos
    GLFWwindow *window;




    // - Tamaño, título de la ventana, en ventana y no en pantalla completa,
    // sin compartir recursos con otras ventanas.
    window = glfwCreateWindow( 1024, 576, "Practica 1", nullptr, nullptr);


    // - Comprobamos si la creación de la ventana ha tenido éxito.
    if ( window == nullptr )
    { std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }

    // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
    // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent ( window );

    // - Ahora inicializamos GLAD.
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) )
    { std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow ( window ); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

    PAG::Renderer::getInstancia().inicializarOpenGL();




    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, window_refresh_callback );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );
    glfwSetMouseButtonCallback ( window, mouse_button_callback );
    glfwSetScrollCallback ( window, scroll_callback );


    //Inicializar IMGUI con PAG::GUI
    PAG::GUI::getInstancia().inicializar(window);


    //Mensaje para ventana
    PAG::GUI::getInstancia().añadirMensaje("Starting Application PAG - Prueba 01");

// - Ciclo de eventos de la aplicación. La condición de parada es que la
// ventana principal deba cerrarse, por ejemplo, si el usuario pulsa el
// botón de cerrar la ventana (la X).
    while ( !glfwWindowShouldClose ( window ) )
    { // - Obtiene y organiza los eventos pendientes, tales como pulsaciones
// de teclas o de ratón, etc. Siempre al final de cada iteración del
// ciclo de eventos y después de glfwSwapBuffers ( window );

        //Refrescar ventana
        PAG::Renderer::getInstancia().window_refresh();

        // Refresco Interfaz IMGUI
        PAG::GUI::getInstancia().nuevoFrame();


        //Renderizar controles
        PAG::GUI::getInstancia().renderizarControles();


        //Dibujar interfaz
        PAG::GUI::getInstancia().dibujar();


        glfwSwapBuffers(window);
        glfwPollEvents ();

    }



    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << "Finishing application Practica 1" << std::endl;
    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;

    //Destruiz interfaz PAG::GUI
    PAG::GUI::getInstancia().finalizar();

    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.

}