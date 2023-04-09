prog: Sprite.o affichage.o Venera.o Entite.o Mc.o 
	g++ -o prog affichage.o Venera.o Sprite.o -lSDL2 -lSDL2_image

Sprite.o : Sprite.cpp Sprite.hpp affichage.hpp
	g++ -Wall Sprite.cpp -c

Entite.o : Entite.cpp Entite.hpp Sprite.hpp
	g++ -Wall Entite.cpp -c
	
Mc.o : Mc.cpp Mc.hpp Entite.hpp 
	g++ -Wall Mc.cpp -c

affichage.o : affichage.cpp affichage.hpp Sprite.hpp
	g++ -Wall affichage.cpp -c

Venera.o : Venera.cpp Venera.hpp affichage.hpp
	g++ -Wall Venera.cpp -c

clean:
	rm -f *.o

vclean: clean
	rm -f prog