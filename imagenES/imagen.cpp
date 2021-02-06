#include <fstream>
#include <string>
#include <math.h>
#include "imagen.h"

using namespace std;

// -------------------------------------------------------------------------------------------------------------------------------
/**
* @class Clase Imagen
* @file imagen.cpp
* @date 20/05/20
* @author Guillermo & Noelia
*/
//METODOS PRIVADOS
void Imagen::allocate(int f, int c) { //HECHO
	img = new unsigned char*[f];
	for (int i=0; i<f;++i)
		img[i] = new unsigned char[c];
}

void Imagen::deallocate() { //HECHO
	int filas=0, cols=0;
	for(int i=0;i<filas;++i)
		delete[] img[i];
	delete[] img;
}

void Imagen::copy(const Imagen& otro) { //HECHO
	//reservamos la memoria necesaria para copiar la imagen.
    allocate(otro.num_filas() , otro.num_columnas());
	//copiamos uno por uno cada elemento del pixel imagen a la imagen que estamos trabajando
    for (int f = 0; f < otro.num_filas(); ++f) {
        for (int c = 0; c < otro.num_columnas(); ++c) {
            asigna_pixel(f,c,otro.valor_pixel(f,c));
        }
    }
}

//METODOS PUBLICOS

Imagen::Imagen(){ //HECHO
	filas = 0;
	cols = 0;
	allocate(filas,cols);
}

Imagen::Imagen(int filas, int cols) { //HECHO
	this->filas=filas;
	this->cols=cols;
	allocate(filas,cols);
}

Imagen::Imagen(const Imagen &img){ // HECHO
	//si habia algo antes, lo borramos
	deallocate();
	copy(img);
}

Imagen::Imagen(unsigned char* vec, int f, int c){ //HECHO
	int contador = 0;	
	filas = f;
	cols = c;
	allocate (filas, cols);
	for (int i=0; i < filas; i++) {
		for (int j=0; j < cols; j++) {
			asigna_pixel(i,j, vec[contador]);
			contador++;
		}
	}
}

Imagen::~Imagen(){ //HECHO
	deallocate();
}

Imagen& Imagen::operator=(const Imagen& orig){ //HECHO
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
    return *this;
}

void Imagen::asigna_pixel(int fila, int col, byte valor){ //HECHO
	if (valor_pixel(fila,col) != valor) {
		img[fila][col] = valor;
	}
}

unsigned char* Imagen::pasar_a_vector() { //HECHO
	unsigned char* vec = new unsigned char[num_filas()*num_columnas()];
	int contador=0;
	for (int i=0; i < num_filas(); i++) {
		for (int j=0; j < num_columnas(); j++) {
			vec[contador] = valor_pixel(i,j);
			contador++;
		}
	}
	return vec;
}

double Imagen::func_media(int i1, int j1, int i2, int j2) { //HECHO
	double media;
	media = (valor_pixel(i1, j1) + valor_pixel(i2, j2))/2;
	return media;
}

bool operator==(const Imagen& izq, const Imagen& dcha) { //HECHO
	bool estado = true;
	if ((izq.num_columnas() != dcha.num_columnas()) || (izq.num_filas() != dcha.num_filas())) {
		estado = false;
	} else {
		for (int i=0; i < izq.num_filas() && estado; i++) {
			for (int j=0; j < izq.num_columnas(); j++) {
				if (izq.valor_pixel(i,j) != dcha.valor_pixel(i,j)) {
					estado = false;
				}
			}
		}
		estado = false;
	}
	return estado;
}

