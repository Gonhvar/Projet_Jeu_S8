prog: affichage.o  
	g++ -o prog affichage.o -lSDL2

affichage.o : affichage.cpp affichage.hpp 
	g++ -Wall affichage.cpp -c

clean:
	rm -f *.o

vclean: clean
	rm -f prog




