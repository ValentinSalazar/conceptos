# Memoria dinámica

En primer lugar, un repaso al compilador.
-> Entender el compilador nos ayudará a ser mejores programadores.
Por qué? Porque sabremos que esta pasando en nuestro programa,
detectar errores y su ciclo de vida.

Pero primero. Qué es el compilador? Resumidamente es un conjunto de programas
que se encarga de traducir nuestro código (texto) al código el cual entienden
las computadores (binario).

Este proceso tiene varias etapas e intervienen varíos componentes del compilador:
- El Lexer, El Parser, La generación de código intermedio y generación de código objeto.

Pero no entraremos en detalle, pues solo nos interesa entender la memoria dinámica.
Una vez que nuestro código fuente llega hasta la etapa de *codigo objeto*, allí
nuestro código *"toma vida"* y es pósible ejecutarlo en alguna máquina.
Además, allí nuestro código que se divide en varias etapas:
- Código. Datos. Call Stack. Heap.

Estas secciones almacenan cierto tipo de información de nuestro programa.

### Call Stack
La Pila de Ejecución es una estructura dinámica en la cuál se almacenan
las variables locales y las instrucciones a ejecutar de nuestro programa.
El Call Stack es controlado por el compilador.
Supongamos que tenemos el siguiente código:
```C
  int sumar_enteros(int a, int b){
    return a + b;
  }

  int main(){
    int suma = sumar_enteros(20, 30); // int suma -> Variable local
    // Sumar enteros -> llamada a función donde se crea otro Frame Call Stack,
    return 0;
  }
```
Cuando se hace la llamada a la función *sumar_enteros*, se genera otro Call Stack aparte,
el cuál tendrá sus propías variables locales, y sus propías llamadas a otras funciones.

### Heap
Esta es una sección que se dedica únicamente a trabajar con memoria dinámica.
En este caso, el compilador no reserva memoría para trabajar aquí, si no
que esto es encargado de realizarlo el programador en **tiempo de ejecución.**
Como el Heap se utiliza en tiempo de ejecución del programa, el compilador ni el
sistema operativo saben a priori que memoria deberá reservar, por lo tanto,
el programador debe ser capaz de reservar la memoria adecuada con la que trabajará.
Una vez utilizada esa memoria, deberá ser liberada.

### Punteros
Los punteros son variables que almacenan direcciones de memoria.
Son muy utilizados para trabajar con memoria dinámica, ya que disponemos
de varías funciones que nos otorga el lenguaje C como:
- Malloc: Reserva el espacio en memoria que le indicamos por parametro y nos retorna
la dirección en memoría en donde se reservó.
- Free: Libera el espacio en memoria que ocupa la dirección que le indicamos por parametro.
- Realloc: Nos permite realocar cierto espacio en memoria. Nos retorna una nueva dirección de memoría.

### Vectores dinámicos
Sabemos que los vectores tienen una cierta longitud *fija* y que una vez definido,
no es posible cambiarla. Por este motivo, entran en juego los **vectores dinámicos.**
La forma de implementarlos es a través de memoría dinámica, es decir, en el Heap.
Para ello, debemos definir un puntero el cual apuntará a un vector en el Heap y
la forma de agrandar o achicar su longitud es pidiendole mas o menos memoria al SO, utilizando
la función Realloc.

Ejemplo 0.1
```C
    int main(){
        int cantidad_elementos = 5;
        int* vector_dinamico = malloc(sizeof(int) * cantidad_elementos);
        int elemento_nuevo;

        for(int i = 0; i < cantidad_elementos; i++){
            printf("ingrese un elemento: ");
            scanf(" %i", &elemento_nuevo);
            *(vector_dinamico + i) = elemento_nuevo;
        }

        free(vector_dinamico);

        return 0;
    }
```
Vemos que definimos una cierta cantidad de elementos en primer instancia, luego le solicitamos
espacio en memoria con la función Malloc y esta nos retorna un puntero al espacio solicitado.
Después le solicitamos elementos al usuario para agregarlos al vector dinámico. Y por último,
una vez que hemos terminado de trabajar con él, liberamos la memoria utilizada.

En caso de querer agregar mas elementos, deberíamos utilizar Realloc.
```C
    int main(){
        int cantidad_elementos = 5;
        int* vector_dinamico = malloc(sizeof(int) * cantidad_elementos);
        if(vector_dinamico == NULL  ){
            printf("Error al reservar espacio de memoria");
            return -1;
        }
        int elemento_nuevo;

        for(int i = 0; i < cantidad_elementos; i++){
            printf("ingrese un elemento: ");
            scanf(" %i", &elemento_nuevo);
            *(vector_dinamico + i) = elemento_nuevo;
        }

        vector_dinamico = realloc(vector_dinamico, sizeof(int) * 3);
        *(vector_dinamico + 5) = 29;
        *(vector_dinamico + 6) = 37;
        *(vector_dinamico + 7) = 52;

        free(vector_dinamico);

        return 0;
    }
```
Entonces, realocamos la dirección con más memoria y le agregamos 3 elementos
nuevos al vector.

### Vectores dinámicos con Structs y manejo de error al asignar memoria
En caso de utilizar un vector dinámico en el cuál almacenaremos un struct,
donde el struct a su vez tiene un vector dinámico, debemos saber liberar la memoria
de manera correcta.

[Gráfico fundamental y explicativo](https://excalidraw.com/#json=E9Uvk6mqHuHkdrZM_dNTZ,3rbcCxy3I0SinrlVkq7j2w)
Ejemplo 0.2
```C
#include <stdlib.h>
#include <stdio.h>

typedef struct mascota {
    int edad;
    char raza;
} mascota_t;

typedef struct persona {
    int cantidad_mascotas;
    mascota_t* mascotas;
} persona_t;

void imprimir_mascotas(persona_t* personas, int cantidad_personas){
    for(int i = 0; i < cantidad_personas; i++){
        for(int j = 0; j < personas[i].cantidad_mascotas; j++){
            printf("Raza de la mascota: %c\n", personas[i].mascotas[j].raza);
            printf("Edad de la mascota: %i\n", personas[i].mascotas[j].edad);
        }
    }
}

int main(){
    int cantidad_personas;
    printf("Ingrese la cantidad de personas: ");
    scanf(" %i", &cantidad_personas);

    persona_t* personas = malloc(sizeof(persona_t) * cantidad_personas);
    if(personas == NULL) {
        printf("Error de memoria.");
        return -1;
    }

    for(int i = 0; i < cantidad_personas; i++){
        int cantidad_mascotas;
        printf("Ingrese la cantidad de mascota de la persona %i: ", i+1);
        scanf(" %i", &cantidad_mascotas);

        personas[i].cantidad_mascotas = cantidad_mascotas;
        mascota_t* mascotas = malloc(sizeof(mascota_t) * cantidad_mascotas);
        if(mascotas == NULL){
            printf("Error de memoria al asignar mascotas. Por ende, libero las que se hayan reservado correctamente anteriormente.");
            for(int p = 0; p < i; p++){
                free(personas[p].mascotas);
            }
            free(personas);
            return -1;
        }
        personas[i].mascotas = mascotas;

        for(int j = 0; j < cantidad_mascotas; j++){
            printf("Ingrese la edad de la mascota %i: ", j+1);
            scanf(" %i", &personas[i].mascotas[j].edad);
            printf(" Ingrese la raza %i: ", j+1);
            scanf(" %c", &personas[i].mascotas[j].raza);
        }
    }

    imprimir_mascotas(personas, cantidad_personas);

    for(int i = 0; i < cantidad_personas; i++){
        free(personas[i].mascotas);
    }

    free(personas);

    return 0;
}
```

### Punteros en funciones
Otro de los casos donde podemos utilizar punteros es en funciones.

El objetivo es evitar que nuestro programa realice una copia de los valores que le
damos por parametro y trabajar directamente con las direcciones de memoria de
los elementos que le indicamos por parametro.

Suponte que queremos realizar una función que no retorna nada, solo realiza
cambios en los valores que le pasamos por parametro.

En primer lugar cuando invocamos la función, debemos indicarle la dirección de memoria con las que estará trabajando. Y luego, en la función misma, debemos desreferenciar los punteros para poder obtener los valores concretos.

*Para obtener la dirección de memoria de una variable entera (o cualquier tipo)
se utiliza el simbolo &*

Ya que si no, estaremos trabajando con las direcciones y no con los valores que
poseen las direcciones.

*Para poder desreferenciar las direcciones de memorias, utilizamos **

Ejemplo simple: La dirección de memoría 0x23AF almacena el valor del número entero 47.

Nosotros cuando invoquemos la función le indicamos la dirección 0x23AF y luego,
en la función la desreferenciamos para obtener el valor del numero entero 47.

Ejemplo 03
```C
    #include <stdio.h>

    void multiplicar_enteros(int* numeroA, int* numeroB, int* producto){
        *producto = (*numeroA) * (*numeroB);
    }

    int main(){
        int primer_entero = 20;
        int segundo_entero = 3;
        int producto = 0;

        multiplicar_enteros(&primer_entero, &segundo_entero, &producto);

        printf("El producto entre %i y %i es %i\n", primer_entero, segundo_entero, producto);
        return 0;
    }


```
