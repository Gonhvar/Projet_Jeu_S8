prog: Sprite.o affichage.o Entite.o Killable.o Mc.o Venera.o Drop.o Enemies.o BasicSkeleton.o SpawnPoint.o Attacks.o
	g++ -o prog Sprite.o affichage.o Entite.o Killable.o Mc.o Venera.o Drop.o Enemies.o BasicSkeleton.o SpawnPoint.o Attacks.o -lSDL2 -lSDL2_image -lSDL2_ttf



Sprite.o : Sprite.cpp Sprite.hpp affichage.hpp
	g++ -Wall Sprite.cpp -c

Entite.o : Entite.cpp Entite.hpp Sprite.hpp Venera.hpp
	g++ -Wall Entite.cpp -c

Killable.o : Killable.cpp Killable.hpp Entite.hpp
	g++ -Wall Killable.cpp -c

Mc.o : Mc.cpp Mc.hpp Killable.hpp Attacks.hpp
	g++ -Wall Mc.cpp -c
	
Drop.o : Drop.cpp Drop.hpp Killable.hpp 
	g++ -Wall Drop.cpp -c

Enemies.o : Enemies.cpp Enemies.hpp Drop.hpp 
	g++ -Wall Enemies.cpp -c

Attacks.o : Attacks.cpp Attacks.hpp Mc.hpp
	g++ -Wall Attacks.cpp -c

BasicSkeleton.o : BasicSkeleton.cpp BasicSkeleton.hpp Enemies.hpp 
	g++ -Wall BasicSkeleton.cpp -c

SpawnPoint.o : SpawnPoint.cpp SpawnPoint.hpp Entite.hpp
	g++ -Wall SpawnPoint.cpp -c

affichage.o : affichage.cpp affichage.hpp Sprite.hpp Mc.hpp
	g++ -Wall affichage.cpp -c

camera.o : Camera.cpp Camera.hpp 
	g++ -Wall Camera.cpp -c

Venera.o : Venera.cpp Venera.hpp affichage.hpp Killable.hpp Mc.hpp BasicSkeleton.hpp SpawnPoint.hpp
	g++ -Wall Venera.cpp -c

clean:
	rm -f *.o

vclean: clean
	rm -f prog
