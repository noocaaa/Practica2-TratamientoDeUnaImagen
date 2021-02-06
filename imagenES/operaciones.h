typedef unsigned char byte;

#ifndef _OPERACIONES_H
#define _OPERACIONES_H

/**
  * @file operaciones.h
  * @brief Fichero cabecera para las operaciones que se realizan con las imagenes a partir de ficheros
  * @author Guillermo & Noelia
  * @date 15/11/20
  */

/**
* @brief  Umbralizar una imagen usando una escala de grises
* @param <fichE> nombre fichero contiene imagen original
* @param <fichS> nombre fichero contiene resultado de la transformaci�n
* @param T_1, T_2 valores del intervalo de la umbralizaci�n
* @pre Supondremos que el fichero pasado cumple con el requisito de PGM. Es decir, no tendra ninguna letra.
*/
void umbralizar_imagen(const char* fichE, const char* fichS, int T_1, int T_2);

/** @brief Hacemos zoom a una parte de la imagen.
* @param fichE, fichero de entrada
* @param fichS, fichero de salida
* @param x_1, fila superior de la imagen
* @param y_1, columna superior de la imagen
* @param x_2, fila inferior de la imagen
* @param y_2, columna inferior de la imagen.
*/
void zoom_imagen(const char* fichE, const char* fichS, int x_1, int y_1, int x_2, int y_2);

/**
* @brief aumento de contraste de la imagen
* @param fichE, fichero de entrada
* @param fichS, fichero de salida
* @param min valor minimo del nuevo rango
* @param max valor maximo del nuevo rango
* @pre se supone que min y max son enteros.
*/
void aumento_contraste(const char* fichE, const char* fichS, int min, int max);

/**
 * @brief Funcion que de una imagen llega a otra
 * @param fich1, la imagen de la que se parte
 * @param fich2, la imagen a la que se quiere llegar
 */
void morphing(const char* fich1, const char* fich2);

#endif
