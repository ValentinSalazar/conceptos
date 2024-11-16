#include <stdlib.h>
#include <stdio.h>

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
