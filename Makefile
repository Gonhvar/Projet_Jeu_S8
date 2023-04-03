prog: affichage.o  Venera.o
	g++ -o prog affichage.o Venera.o -lSDL2

Venera.o : Venera.cpp Venera.hpp 
	g++ -Wall Venera.cpp -c


affichage.o : affichage.cpp affichage.hpp 
	g++ -Wall affichage.cpp -c

clean:
	rm -f *.o

vclean: clean
	rm -f prog




