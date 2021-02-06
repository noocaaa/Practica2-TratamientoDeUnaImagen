main: main.o imagenES.o imagen.o operaciones.o
	g++ -std=c++11 main.o imagenES.o imagen.o operaciones.o -o main

main.o: main.cpp
	g++ -std=c++11 -g -c -o main.o -I. main.cpp 

imagenES.o: imagenES.cpp imagenES.h
	g++ -std=c++11 -g -c -o imagenES.o -I. imagenES.cpp

imagen.o: imagen.cpp imagen.h
	g++ -std=c++11 -g -c -o imagen.o -I. imagen.cpp

operaciones.o: operaciones.cpp operaciones.h
	g++ -std=c++11 -g -c -o operaciones.o -I. operaciones.cpp

documentation:
	doxygen

clean:
	-rm *.o negativo
