#include "imagenES.h"
#ifndef _IMAGEN_H
#define _IMAGEN_H
typedef unsigned char byte; // tipo base de cada pixel

/**
 * @file imagen.h
 * @class Clase Imagen
 * @brief Implementación del TDA imagen (imagen digital en niveles de gris)
 * @date 20/05/20
 * @author Guillermo & Noelia
 */
class Imagen {
	private:
		int filas; // Numero de filas de la imagen
		int cols; // Numero de columnas de la imagen
		byte **img; // La imagen en si: una matriz dinamica 2D de bytes

		/**
		* @brief Liberar la memoria usada
		*/
		void deallocate();

		/**
		* @brief reservaba memoria dinamica de una matriz m[f][c]
		* @param f, número de filas
		* @param c, número de columnas
		*/
		void allocate(int f, int c);

		/*
		* @brief función de copia de imagen.
		* @param otro, objeto de la clase imagen
		*/
		void copy(const Imagen& otro);

	public:
		/**
		 * @brief Constructor por defecto
		 */
		Imagen(); //Ejemplo de uso: Imagen I;

		/**
		 * @brief constructor de copia
		 * @param img de la clase imagen
		 */
		Imagen(const Imagen &img); //Ejemplo de uso: Imagen I(J);

		/**
		 * @brief Crear una imagen en memoria con filas filas y cols columnas. Reserva memoria para alojar la imagen.
		 * @param filas, numero de filas que tendrá la nueva imagen
		 * @param cols, numero de columnas que tendrá la nueva imagen
		 * @pre filas > 0
		 * @pre cols > 0
		 * @warning Operación de tipo constructor
		 * @post La imagen creada contiene "filas" filas y "cols" columnas.
		 * @post La imagen creada no esta inicializada.
		 * @return nos devuelve la imagen creada a partir de los datos proporcionados
		 */
		Imagen(int filas, int cols); //Ejemplo de uso: Imagen I(10,10);

		/**
		 * @brief Operador de asignación.
		 * @param img de la clase img
		 */
		Imagen& operator=(const Imagen& img);

		/**
		 * @brief Constructor de la clase imagen.
		 * @param vec, que contiene los valores de la imgen
		 * @param f, numero de filas de la imagen
		 * @param c. numero de columnas de la imagen
		 */
		Imagen(unsigned char* vec, int f, int c);

		/**
		 * @brief Liberar los recursos ocupados por la imagen
		 * @warning Operación de tipo de tipo destructor
		 * @post no devuelve nada
		 * @post La imagen destruida no puede usarse, salvo que se cree de nuevo.
		 */
		~Imagen();

		/**
		 * @brief Calcular el numero de filas de la imagen
		 * @post devuelve el numero entero de filas de la imagen
		 * @post La imagen no se modifica
		 */
		inline int num_filas() const{ //Ejemplo de uso: I.num_filas();
			return filas;
		}

		/**
		 * @brief Calcular el numero de columnas de la imagen
		 * @post devuelve el numero entero de columnas de la imagen
		 * @post la imagen no se modifica.
		 */
		inline int num_columnas() const{  //Ejemplo de uso: I.num_columnas();
			return cols;
		}

		/**
		 * @brief Asignar el valor de luminosidad valor a la casilla (fila, col) de la imagen.
		 * @param fila, entero fila de la imagen donde escribir
		 * @param col, entero columna de la imagen donde escribir
		 * @param valor, byte valor de la imagen que se escribira en la posición indicada
		 * @pre 0 <= "fila" < i.num_filas()
		 * @pre 0 <= "col" < i.num_columnas()
		 * @pre 0 <= valor <= 255
		 * @post devuelve void, es decir, nada.
		 * @post La imagen se modifica. Concretamente, se cambia el valor de la casilla (fila, col) de la imagen por el especificado con valor. Los restantes puntos no se modifican.
		 */
		void asigna_pixel(int fila, int col, byte valor); //Ejemplo de uso: I.num_columnas();

		/**
		 * @brief Consultar el valor de la casilla ("fila", "col") de la imagen
		 * @param fila, fila de la imagen a consultar
		 * @param col, columna de la imagen a consultar
		 * @pre 0 <= "fila" < i.num_filas ()
		 * @pre 0 <= "col" < i.num_columnas ()
		 * @post Devuelve: El valor de luminosidad de la casilla (fila, col) de la imagen, que está en el conjunto {0,1, ...., 255}.
		 * @post La imagen no se modifica.
		 */
		inline byte valor_pixel(int fila, int col) const {
			return img[fila][col];
		}
		
		/**
		* @brief funcion que calcula la media entre dos pixeles
		* @param i1, la posicion x del primer pixel
		* @param j1, la posicion y del primer pixel
		* @param i2, la posicion x del segundo pixel
		* @param j2, la posicion y del segundo pixel
		* @return devuelve la media de los valores de dichos pixeles
		*/
		double func_media(int i1, int j1, int i2, int j2);

		/**
		 * @brief Funcion que pasa la imagen a un vector
		 * @return nos devuelve un vector de tipo unsigned char*
		 */
		unsigned char* pasar_a_vector();

};


/**
 * @brief operación de comparación entre dos imagenes
 * @param izq, una de las dos imagenes a comparar
 * @param dcha, la otra imagen a comparar
 * @return devuelve true si son iguales, false si son diferentes
 */
bool operator==(const Imagen& izq, const Imagen& dcha);

#endif

/* Fin Fichero: imagen.h */
