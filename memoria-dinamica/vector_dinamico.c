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
            printf("Error de memoria al asignar mascotas.");
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
