/**
  * @file main.cpp
  * @brief Fichero que contiene un switch con varias opciones que tratan con imagenes
  * @author Guillermo & Noelia
  * @date 17/11/20
  */

#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

#include "imagenES.h"
#include "imagen.h"
#include "operaciones.h"

using namespace std;

int main (int argc, char *argv[]){

  char *origen, *destino; // nombres de los ficheros
  unsigned char *image1, *image2;
  int nf, nc, npixeles; // Num. de filas y columnas de las imagenes
  int opcion; //opción escogida por el usuario
  int n, m;
  int f=0, c=0;

  // Comprobar validez de la llamada
  if (argc != 3){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Se deben pasar dos parametro en todo momento \n";
    exit (1);
  }
 
 //ejecutamos el menú mientras que no se introduza un seis
 do {
	  cout << endl << endl;
	  cout << "Menú de opciones: " << endl << endl;
	  cout << "Opción 1: Hacer el negativo de la imagen" << endl;
	  cout << "Opción 2: Umbralizar la imagen" << endl;
	  cout << "Opción 3: Hacer el zoom de la imagen" << endl;
	  cout << "Opción 4: Aumentar el contraste de la imagen" << endl;
	  cout << "Opción 5: Morphing entre dos imagenes" << endl;
	  cout << "Opción 6: Salir" << endl;

	  cout << "Ingrese una opción: ";
	  cin >> opcion;

	  if (opcion < 6) {
		origen = argv[1];
		destino = argv[2];

		if (opcion !=5) {
			// Leer la imagen del fichero de entrada
			image1 = LeerImagenPGM (origen, nf, nc);

			if (!image1){
			    cerr << "Error: No pudo leerse la imagen." << endl;
			    cerr << "Terminando la ejecucion del programa." << endl;
			    exit (1);
			}

			// Mostrar los parametros calculados por LeerImagenPGM()
			cout << endl;
			cout << "Dimensiones de " << origen << ":" << endl;
			cout << "Imagen = " << nf  << " filas x " << nc << " columnas " << endl;
		} else {

			// Leemos las imagenes de los ficheros de entrada
			image1 = LeerImagenPGM (origen, nf, nc);
			image2 = LeerImagenPGM (destino, f, c);

			if (!image1){
			    cerr << "Error: No pudo leerse la primera imagen." << endl;
			    cerr << "Terminando la ejecucion del programa." << endl;
			    exit (1);
			} else if (!image2) {
			    cerr << "Error: No pudo leerse la segunda imagen." << endl;
			    cerr << "Terminando la ejecucion del programa." << endl;
			    exit (1);
			}

			// Mostrar los parametros de cada imagen
			cout << endl;
			cout << "Dimensiones de la primera imagen " << origen << ":" << endl;
			cout << "Imagen 1 = " << nf  << " filas x " << nc << " columnas " << endl;

			cout << endl;
			cout << "Dimensiones de la segunda imagen " << origen << ":" << endl;
			cout << "Imagen 2 = " << f << " filas x " << c << " columnas " << endl;
		}

	  }

	  //hacemos un switch con cada opción correspondiente
	  switch (opcion) {
		case 1: //código copiado del fichero negativo.cpp de Joaquín Valdivia
			// Calcular el negativo
			npixeles = nf*nc;
			for (int i=0; i<npixeles; i++)
			    image1[i] =  255 - image1[i];

			// Guardar la imagen resultado en el fichero
			if (EscribirImagenPGM (destino, image1, nf, nc))
			    cout  << "La imagen se guardo en " << destino << endl;
			else{
			    cerr << "Error: No pudo guardarse la imagen." << endl;
			    cerr << "Terminando la ejecucion del programa." << endl;
			    exit (2);
			} 		

			break;

		case 2:
			//preguntamos entre que dos valores se quiere umbralizar
			cout << endl << endl;
			cout << "Decida entre que dos valores quiere umbralizar la imagen." << endl;
			cout << "Valor uno: ";
			cin >> n;
			cout << "Valor dos: ";
			cin >> m;

			//comprobamos que los parametros introducidos son válidos
			if (n < 0 || m < 0) {
				cerr << "Los valores deben ser un número positivo";
				exit(1);
			} else if (n > m) {
				cerr << "El primer valor introducido debe ser menor al segundo valor introducido";
				exit(1);				
			}

			umbralizar_imagen(origen,destino,n,m);
			break;

		case 3:
			int x1, x2, x3, x4;
			//preguntamos la zona en la que se quiere hacer zoom
			cout << endl << endl;
			cout << "Decida en que parte de la imagen quiere hacer zoom." << endl;
			cout << "Numero de fila del pixel que esta en la esquina superior: ";
			cin >> x1;
			cout << endl << "Numero de columna del pixel que esta en la esquina superior: ";
			cin >> x2;
			cout << endl << "Numero de fila del pixel que esta en la esquina inferior: ";
			cin >> x3;
			cout << endl << "Numero de columna del pixel que esta en la esquina inferior: ";
			cin >> x4;

			//comprobamos que los parametros introducidos son válidos
			if ((x3 - x1) != (x4 - x2)) {
 				cerr << "Deben ser una matriz cuadrada" << endl;
				exit(1);
			} else if (x1 > nf || x2 > nc || x1 < 0 || x2 < 0 || x3 > nf || x4 > nc || x3 < 0 || x4 < 0) {
				cerr << "Deben ser unos valores de filas y columnas que se encuentren dentro de la imagen" << endl;
				exit(1);
			}

			zoom_imagen(origen, destino, x1, x2, x3, x4);
			break;

		case 4:
			//preguntamos entre que dos valores se quiere umbralizar
			cout << endl << endl;
			cout << "Decida entre que dos valores quiere tener el constraste" << endl;
			cout << "Valor uno: ";
			cin >> n;
			cout << "Valor dos: ";
			cin >> m;

			//comprobamos que los parametros introducidos son válidos
			if (n < 0 || m < 0) {
				cerr << "Los valores deben ser un número positivo";
				exit(1);
			} else if (n > m) {
				cerr << "El primer valor introducido debe ser menor al segundo valor introducido";
				exit(1);				
			}

			aumento_contraste(origen, destino, n, m);
			break;

		case 5:
			morphing(origen, destino);
			//liberamos memoria
			delete[] image2;
			break;
	  } 

  } while (opcion != 6);

  // Liberar la imagen
  delete[] image1;

  return (0);
}
