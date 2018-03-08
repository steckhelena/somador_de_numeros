/* Somador de numeros
 * Marco Antonio Steck Filho
 * RA - 183374
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 64

// Estados de uma maquina de estados
typedef enum {start, space, number, factorial, point, point_number} states;

// Token simples para ser usado pela maquina de estado buferizando um numero
typedef struct {
	int pos;
	char tok[MAX_SIZE];
} token;

// Retorna o fatorial de um numero
int do_factorial(int factorial) {
	int i = 1;
	int result = 1;

	for (; i-1 < factorial; i++) {
		result *= i;
	}

	return result;
}

int main() {
	char c; // Entrada da maquina de estados
	float result = 0; // Soma dos numeros encontrados na maquina de estados
	states state = space; // Estado inicial da maquina de estados
	token tok; // Token para buferizar os numeros da maquina de estados

	// Loop da maquina de estados
	while ((c = getchar()) != '\n' && c != EOF) {
		if (state == start) {	// Caso o caracter anterior nao foi um espaco ou parte de um numero
			if (c == ' ') {
				state = space;
			}
		} else if (state == space) { // Caso o caracter anterior foi um espaco
			if (isdigit(c)) {
				tok.pos = 0;
				state = number;
				tok.tok[tok.pos++] = c;
			} else if (c =='.') {
				tok.pos = 0;
				state = point;
				tok.tok[tok.pos++] = c;
			} else {
				state = start;
			}
		} else if (state == number) { // Caso o caracter anterior tenha sido um numero.
			if (c == '!') {
				state = factorial;
				tok.tok[tok.pos++] = c;
			} else if (c == '.') {
				tok.tok[tok.pos++] = c;
				state = point;
			} else if (c == ' ') {
				state = space;
				tok.tok[tok.pos++] = '\0';
				result += atof(tok.tok);
			} else if (isdigit(c)) {
				tok.tok[tok.pos++] = c;
			} else {
				state = start;
			}
		} else if (state == factorial) { // Caso o caracter anterior tenha sido um '!'
			if (c == ' ') {
				state = space;
				tok.tok[--tok.pos] = '\0';
				result += do_factorial(atoi(tok.tok));
			} else if (isdigit(c)) {
				tok.tok[tok.pos++] = c;
			} else {
				state = start;
			}
		} else if (state == point) { // Caso o caracter anterior tenha sido um '.'
			if (c == ' ') {
				state = space;
			} else if (isdigit(c)) {
				tok.tok[tok.pos++] = c;
				state = point_number;
			} else {
				state = start;
			}
		} else if (state == point_number) { // Caso o caracter anterior tenha sido um numero parte de um float
			if (c == ' ') {
				state = space;
				tok.tok[tok.pos++] = '\0';
				result += atof(tok.tok);
			} else if (isdigit(c)) {
				tok.tok[tok.pos++] = c;
			} else {
				state = start;
			}
		}
	}

	// Checagem pelo fim do loop.
	if (state == factorial) {
		tok.tok[--tok.pos] = '\0';
		result += do_factorial(atoi(tok.tok));
	} else if (state == point_number || state == number) {
		tok.tok[tok.pos++] = '\0';
		result += atof(tok.tok);
	}

	// Mostra o resultado da soma de todos os numeros encontrados na entrada.
	printf("%0.2f\n", result);

	return 0;
}
