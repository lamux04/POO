all: prueba

CXX = c++

Fecha.o: Fecha.cpp Fecha.hpp
	$(CXX) -c Fecha.cpp

main.o: main.cpp Fecha.hpp
	$(CXX) -c main.cpp

prueba: Fecha.o main.o
	$(CXX) -o prueba Fecha.o main.o

clean:
	rm *.o prueba