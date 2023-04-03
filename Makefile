prog: Projet.o  
	g++ -o prog Projet.o

Projet.o : Projet.cpp Projet.hpp 
	g++ -Wall Projet.cpp -c

clean:
	rm -f *.o

vclean: clean
	rm -f prog




