prog: affichage.o Venera.o Sprite.o 
	g++ -o prog affichage.o Venera.o Sprite.o -lSDL2

Sprite.o : Sprite.cpp Sprite.hpp
	g++ -Wall Sprite.cpp -c

Venera.o : Venera.cpp Venera.hpp 
	g++ -Wall Venera.cpp -c

affichage.o : affichage.cpp affichage.hpp Sprite.hpp
	g++ -Wall affichage.cpp -c

clean:
	rm -f *.o

vclean: clean
	rm -f prog




