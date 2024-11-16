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
