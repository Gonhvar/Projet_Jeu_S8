prog: Sprite.o affichage.o Entite.o Mc.o Venera.o Drop.o Enemies.o BasicSkeleton.o 
	g++ -o prog Sprite.o affichage.o Entite.o Mc.o Venera.o Drop.o Enemies.o BasicSkeleton.o -lSDL2 -lSDL2_image

Sprite.o : Sprite.cpp Sprite.hpp affichage.hpp
	g++ -Wall Sprite.cpp -c

Entite.o : Entite.cpp Entite.hpp Sprite.hpp
	g++ -Wall Entite.cpp -c
	
Mc.o : Mc.cpp Mc.hpp Entite.hpp 
	g++ -Wall Mc.cpp -c
	
Drop.o : Drop.cpp Drop.hpp Entite.hpp 
	g++ -Wall Drop.cpp -c

Enemies.o : Enemies.cpp Enemies.hpp Drop.hpp 
	g++ -Wall Enemies.cpp -c

BasicSkeleton.o : BasicSkeleton.cpp BasicSkeleton.hpp Enemies.hpp 
	g++ -Wall BasicSkeleton.cpp -c

affichage.o : affichage.cpp affichage.hpp Sprite.hpp
	g++ -Wall affichage.cpp -c

camera.o : Camera.cpp Camera.hpp 
	g++ -Wall Camera.cpp -c

Venera.o : Venera.cpp Venera.hpp affichage.hpp Entite.hpp Mc.hpp
	g++ -Wall Venera.cpp -c

clean:
	rm -f *.o

vclean: clean
	rm -f prog
