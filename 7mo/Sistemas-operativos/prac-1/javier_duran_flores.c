#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

/* Author:
	Javier Duran Flores
*/

// PROTOTIPOS
void accionHijo1(int );
void ordenamientoBurbuja(int[], int );
void imprimirArreglo(int[] , int );
void accionHijo2(float , int );
void accionHijo3(char * );
int contarVocales(char *);

int main (int argc, char * argv[]) {
	if (atoi(argv[1]) > 0) {
		if (atoi(argv[2]) > 0) {

			pid_t pid_hijo1,
				  pid_hijo2,
				  pid_hijo3;

			pid_hijo1 = fork();
			if(pid_hijo1 == 0) {
				printf("\nproc. hijo 1 con PID = %d, ppid es %d \n", getpid(), getppid());
				accionHijo1(atoi(argv[1]));
				sleep(1);
				exit(0);
			} else {
				wait(NULL);
			}

			pid_hijo2 = fork();
			if(pid_hijo2 == 0) {
				printf("\nproc. hijo 2 con PID = %d, ppid es %d \n", getpid(), getppid());
				accionHijo2(atof(argv[2]), atoi(argv[1]));
				sleep(1);
				exit(0);
			} else {
				wait(NULL);
			}

			pid_hijo3 = fork();
			if(pid_hijo3 == 0) {
				printf("\nproc. hijo 3 con PID = %d, ppid es %d \n", getpid(), getppid());
				accionHijo3(argv[3]);
				sleep(1);
				exit(0);
			} else {
				wait(NULL);
			}
		} else {
			printf("parametro (%s) error\n", argv[1]);
		}
	} else {
		printf("parametro (%s) error\n", argv[1]);
	}
	return 0;

}

/*
	El hijo uno utilizara el primer parametro y validara si esta entre 1 y 10, sino esta
	en ese rango mandara un mensaje de "VALOR NO VALIDO, DEBE SER ENTRE 1 Y 10". Si pasa
	la validacion deberá pedir la cantidad de numeros que diga el parámetro y almacenarlos
	en un arreglo y ordenarlos.

	Mostrar el arreglo ordenado.
*/
void accionHijo1(int n) {

	int numeros[n];
	for (int i = 0; i < n; i++) {
		printf("Digite numero[%i]: ", (i+1));
		scanf("%d", &numeros[i]);
	}

	printf("\ncadena normal\n");
	for (int i = 0; i < n; i++)
		printf("%d ", numeros[i]);
	ordenamientoBurbuja(numeros, n);
}

void ordenamientoBurbuja(int v[], int util_v) {
	int temp, i, j;

    for (int i = 0; i < util_v -1 ; i++) {
		for (j = i + 1; j < util_v ; j++) {
			if (v[i] > v[j]) {
				temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}
		}
	}
	printf("\ncadena ordenada\n");
	imprimirArreglo(v, util_v);
}

void imprimirArreglo(int v[], int util_v) {
	for (int i = 0; i < util_v ; i++)
		printf("%d ", v[i]);
	printf("\n");
}

/*
	El hijo 2 utilizara el numero decimal y lo imprimirá el número de veces que indique el primer parámetro.
*/
void accionHijo2(float valor, int n) {
	for (int i = 0; i < n; i++)
		printf("\n(%d). %.2f\n", (i+1), valor);
}

/*
	El hijo 3 analizara la cadena y determinara el número de vocales que tenga. Mostrará ese valor en pantalla.
*/
void accionHijo3(char * cadena) {
	if (contarVocales(cadena) > 0)
		printf("\nNumero de vocales %d de la palabra %s\n", contarVocales(cadena), cadena);
	else
		printf("\nSin vocales\n");
}

int contarVocales(char *cadena){
	int vocales = 0;

	// Recorrer toda la cadena
	for (int indice = 0; cadena[indice] != '\0'; ++indice){

		// Obtener el char de la posición en donde está el índice
		// y por otro lado convertirla a minúscula

		// Así no importa si ponen 'A' o 'a', ambas letras serán convertidas a 'a'
		char letraActual = tolower(cadena[indice]);

		if (
			letraActual == 'a' ||
			letraActual == 'e' ||
			letraActual == 'i' ||
			letraActual == 'o' ||
			letraActual == 'u'
			)
		{
			vocales++;
		}
	}
	return vocales;
}