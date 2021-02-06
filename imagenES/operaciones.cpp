
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "imagenES.h"
#include "imagen.h"
#include "operaciones.h"

using namespace std;

/**
  * @file operaciones.cpp
  * @brief Fichero que contiene las operaciones que se realizan con las imagenes a partir de ficheros
  * @author Guillermo & Noelia
  * @date 15/11/20
  */


void umbralizar_imagen(const char* fichE, const char* fichS, int T_1, int T_2) { // DONE Y COMPROBADO

	//no usamos un objeto de la clase imagen, porque con el vector es el que contiene los valores

	int valor;
 	unsigned char* vec;
	int contador = 0;
	int nf, nc;
	nf = nc = 0;

	//nos informamos de que tipo es la imagen
	TipoImagen tipo = LeerTipoImagen(fichE);


	if (tipo == IMG_PGM) { //si el tipo corresponde con PGM
		//copiamos la imagen del fichero de entrada
		vec = LeerImagenPGM(fichE, nf, nc);

		//umbralizamos la imagen
		contador = 0; //lo ponemos a 0

		for (int i = 0; i < nf*nc; i++) {
			valor = vec[i];
			if (valor <= T_1 || valor >= T_2) {
				vec[contador] = 255;
				contador++;
			} else {
				contador++;
			}
		}

		//escribimos la imagen en el fichero de salida
		EscribirImagenPGM(fichS, vec, nf, nc);
	}

	//liberamos la memoria usada de forma temporal
	delete[] vec;
}

void zoom_imagen(const char* fichE, const char* fichS, int x_1, int y_1, int x_2, int y_2) {

	int nf, nc;
	int contador;
	double media;
	int nfil = x_2 - x_1 + 1; //empezamos con (0,0)
	int ncol = y_2 - y_1 + 1;
	int f, c;
	int r, t; //fila, columna respectivamente
	unsigned char* vec;
	//unsigned char* vecfinal;

	nf = contador = nc = f = c = 0;

	if (nfil == ncol) { //tiene que ser cuadrado

		TipoImagen tipo = LeerTipoImagen(fichE);

		//si es imagen PGM, podremos interpolar
		if (tipo == IMG_PGM) {

			//copiamos la imagen del fichero de entrada
			vec = LeerImagenPGM(fichE, nf, nc);

			Imagen imagen(vec, nf, nc);

			Imagen aux(nfil, ncol); //se hace para tener los elementos del zoom (de la esquina superior a inferior)

			//cogemos los valores de la imagen que estan en el rango (x1,y1) y (x2,y2)
			for (int i = x_1; i <= x_2; i++) { // num filas
				for (int j = y_1; j <= y_2; j++) { //num columnas
					aux.asigna_pixel(f, c, imagen.valor_pixel(i,j));
					c++;
				}
				c=0;
				f++;
			}

			Imagen aux2(aux.num_filas(),2*aux.num_columnas() - 1);

			r = t = 0;
			//interpolamos las columnas
			for (int i = 0; i < aux.num_filas() - 1; i++) {
				for (int j = 0; j < aux.num_columnas() - 1; j++) {
					media = aux.func_media(i,j,i,j+1);
					aux2.asigna_pixel(r, t, aux.valor_pixel(i, j));
					t++;
					//redondeamos. Separamos parte decimal y la parte entera
					aux2.asigna_pixel(r, t, round(media));
					t++;
					aux2.asigna_pixel(r, t, aux.valor_pixel(i, j+1)); //lo sobreescribimos en el siguiente bucle			
				}
				t = 0;
				r++;
			}

			Imagen aux3(2*aux.num_filas() - 1, aux2.num_columnas());

			//interpolamos las filas
			media = r = t = 0;
			for (int i = 0; i < aux2.num_columnas() - 1; i++) {
				for (int j = 0; j < aux2.num_filas() - 1; j++) {
					media = aux2.func_media (j,i,j+1,i);
					aux3.asigna_pixel(r, t, aux2.valor_pixel(j, i));
					r++;					
					//redondeamos. Separamos parte decimal y la parte entera
					aux3.asigna_pixel(r, t, round(media));
					r++;
					aux3.asigna_pixel(r, t, aux2.valor_pixel(j+1, i)); //se sobreescribe
				}
				r = 0;
				t++;
			}
			
			//hay que escribirlo
			EscribirImagenPGM(fichS, aux3.pasar_a_vector(), aux3.num_filas(), aux3.num_columnas()); 

			//liberamos la memoria usada de forma temporal
			delete[] vec;
		}

	}

}

void aumento_contraste(const char* fichE, const char* fichS, int min, int max) {

	unsigned char* vec;
	double val;
	int a = -1, b = -2; // a minimo, b maximo. Valores erroneos
	int nf = 0, nc = 0; //numero filas y numero columnas respectivamente
	int temp; //para saber el valor de la imagen antes del cambio
	double calculo;
	int contador = 0;

	//leemos el tipo de la imagen
	TipoImagen tipo = LeerTipoImagen(fichE);

	if (tipo == IMG_PGM) { //si el tipo de la imagen, es el que esperamos
		//copiamos la imagen del fichero de entrada
		vec = LeerImagenPGM(fichE, nf, nc);

		Imagen aux(vec, nf, nc);

		//asignamos el valor del vector a la imagen auxiliar. Y buscamos el minimo y el maximo
		for (int i = 0; i < aux.num_filas(); i++) {
			for (int j = 0; j < aux.num_columnas(); j++) {
				if (b > aux.valor_pixel(i,j)) { // valor maximo
					b = aux.valor_pixel(i, j);
				}
				else if (aux.valor_pixel(i, j) < a) { //valor minimo
					a = aux.valor_pixel(i, j);
				}
			}
		}

		//calculamos el valor constante
		val = (max - min) / (b - a);

		//y ahora lo transformamos recorriendo toda la matriz
		for (int i = 0; i < aux.num_filas(); i++) {
			for (int j = 0; j < aux.num_columnas(); j++) {
				temp = aux.valor_pixel(i, j) - a;
				if (val == 0 || temp == 0) {
					aux.asigna_pixel(i, j, min);
				} else {
					calculo = min + val*temp;
					aux.asigna_pixel(i,j,round(calculo));
				}
			}
		}

		//escribimos la imagen en el fichero de salida
		EscribirImagenPGM(fichS, aux.pasar_a_vector(), aux.num_filas(), aux.num_columnas());
	}

	//liberamos la memoria usada de forma temporal
	delete [] vec;
}

void morphing(const char* fich1, const char* fich2){ // DONE Y COMPROBADO

	unsigned char* vec1;
	unsigned char* vec2;
	int nf1, nc1, nf2, nc2, contador, media1;
	nf1 = nc1 = nf2 = nc2 = contador = 0;

	vec1 = LeerImagenPGM(fich1, nf1, nc1);
	vec2 = LeerImagenPGM(fich2, nf2, nc2);

	if ((nf1 == nf2) && (nc1 == nc2)) { //si tamaño de las imagenes coincide

		//colocamos cada elemento en la imagen
		Imagen uno(vec1, nf1, nc1);
		Imagen dos(vec2, nf2, nc2);
		Imagen aux(nf1, nc1);

		unsigned char* vecfinal = new unsigned char[nf1*nc1];

		for (int i=0; i < 256 && !(uno == dos); i++) { //para crear los 256 ficheros 
			contador=0;

			//recorremos la imagen para ver el valor de cada pixel
			for (int a=0; a < uno.num_columnas(); a++) {
				for (int b=0; b < uno.num_filas(); b++) {
					if (uno.valor_pixel(a,b) < dos.valor_pixel(a,b)) {
						uno.asigna_pixel(a,b, uno.valor_pixel(a,b) + 1);
					} else if (uno.valor_pixel(a,b) > dos.valor_pixel(a,b)) {
						uno.asigna_pixel(a,b, uno.valor_pixel(a,b) - 1);
					} //si el pixel esta igual, no tenemos que hacer nada
				}
			}
			
			//ponemos el nombre del fichero que sera Mnum.pgm. Siendo num un número comprendido entre 1 y 256
			string cad = "";
			cad += "M"; //para saber que es el morphing

			//para poder ordenarlo para el animate			
			if (i+1 < 10) {
				cad += "00";
			} else if ( i+1 < 100) {
				cad += "0";
			}

			cad += to_string(i+1);
			cad += ".pgm";
			
			//hacemos una conversión de string a const char*
			const char* salida = cad.c_str();
			
			//escribimos la imagen en el fichero
			EscribirImagenPGM(salida, uno.pasar_a_vector(), uno.num_filas(), uno.num_columnas());
		}

	}

	delete[] vec1;
	delete[] vec2;
}
