# include <stdio.h>
# include <stdlib.h>
# include <time.h>
// Esta función calcula la suma de los divisores propios de un número. básicamente recorre todos los números menores a n y suma los que dividen exacto.
int sumaDivisoresPropios(int n) {
    int suma = 0;
    int d = 1;

    while (d < n) {
        if (n % d == 0) {
            suma += d;
        }
        d++;
    }
    return suma;
}
int main(void)
{
int arregloNumeros[15]; // Arreglo donde guardaré 15 números aleatorios
short contador=0;
srand(time(NULL));
printf("El arreglo es: ");
    // arreglo con números entre 0 y 30 y los muestro
while(contador<15)
{
   arregloNumeros[contador] = rand() % 31;
        printf("%d ", arregloNumeros[contador]);
        contador++;


}
contador = 0 // Reinicio contador para volver a recorrer el arreglo

    // cada número para ver si es deficiente, perfecto o abundante
while(contador<15)
{
int numer= arregloNumeros[contador];
        int suma = sumaDivisoresPropios(numer);

        printf("%d - ", numer);
// Comparo la suma de sus divisores propios contra el número
        if (suma < numer)
            printf("El numnero es Deficiente\n");
        else if (suma == numer)
            printf("El numero es Perfecto\n");
        else
            printf("El numero es Abundante\n");

        contador++;
    }

    return 0;


}
}
