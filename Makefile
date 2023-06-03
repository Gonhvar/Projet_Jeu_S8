prog: Sprite.o affichage.o Vector2D.o Entite.o Mc.o Venera.o Drop.o Enemies.o BasicSkeleton.o SpawnPoint.o Attacks.o Map.o Stockeur.o Joueur2.o Bullets.o Input.o AudioManager.o SkeletonShooter.o
	g++ -std=c++11 -g -o prog Sprite.o affichage.o Vector2D.o Entite.o Mc.o Venera.o Drop.o Enemies.o BasicSkeleton.o SpawnPoint.o Attacks.o Map.o Stockeur.o Joueur2.o Bullets.o Input.o AudioManager.o SkeletonShooter.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Stockeur.o : Stockeur.cpp Stockeur.hpp Inc.hpp
	g++ -std=c++11 -Wall Stockeur.cpp -c

Sprite.o : Sprite.cpp Sprite.hpp affichage.hpp Map.hpp Stockeur.hpp
	g++ -std=c++11 -Wall Sprite.cpp -c

Vector2D.o : Vector2D.cpp Vector2D.hpp
	g++ -std=c++11 -Wall Vector2D.cpp -c

Entite.o : Entite.cpp Entite.hpp Sprite.hpp Vector2D.hpp
	g++ -std=c++11 -Wall Entite.cpp -c

Bullets.o : Bullets.cpp Bullets.hpp Entite.hpp
	g++ -std=c++11 -Wall Bullets.cpp -c 

Joueur2.o : Joueur2.cpp Joueur2.hpp Sprite.hpp Bullets.hpp
	g++ -std=c++11 -Wall Joueur2.cpp -c
	
Drop.o : Drop.cpp Drop.hpp Entite.hpp 
	g++ -std=c++11 -Wall Drop.cpp -c

Enemies.o : Enemies.cpp Enemies.hpp Drop.hpp Mc.hpp
	g++ -std=c++11 -Wall Enemies.cpp -c

Mc.o : Mc.cpp Mc.hpp Attacks.hpp Joueur2.hpp
	g++ -std=c++11 -Wall Mc.cpp -c

Input.o : Input.cpp Input.hpp Sprite.hpp Mc.hpp
	g++ -std=c++11 -Wall Input.cpp -c

Attacks.o : Attacks.cpp Attacks.hpp Mc.hpp Entite.hpp
	g++ -std=c++11 -Wall Attacks.cpp -c

BasicSkeleton.o : BasicSkeleton.cpp BasicSkeleton.hpp Enemies.hpp 
	g++ -std=c++11 -Wall BasicSkeleton.cpp -c
	
SkeletonShooter.o : SkeletonShooter.cpp SkeletonShooter.hpp Enemies.hpp 
	g++ -std=c++11 -Wall SkeletonShooter.cpp -c

SpawnPoint.o : SpawnPoint.cpp SpawnPoint.hpp Entite.hpp
	g++ -std=c++11 -Wall SpawnPoint.cpp -c

affichage.o : affichage.cpp affichage.hpp Sprite.hpp Mc.hpp
	g++ -std=c++11 -Wall affichage.cpp -c

camera.o : Camera.cpp Camera.hpp 
	g++ -std=c++11 -Wall Camera.cpp -c

AudioManager.o : AudioManager.cpp AudioManager.hpp
	g++ -std=c++11 -Wall AudioManager.cpp -c

Venera.o : Venera.cpp Venera.hpp affichage.hpp Mc.hpp SpawnPoint.hpp Joueur2.hpp Input.hpp AudioManager.hpp
	g++ -std=c++11 -Wall Venera.cpp -c

Map.o : Map.cpp Map.hpp Venera.hpp
	g++ -std=c++11 -Wall Map.cpp -c
	



clean:
	rm -f *.o

vclean: clean
	rm -f prog
