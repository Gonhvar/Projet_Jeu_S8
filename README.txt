VENERA :
Tous éléments ci-présent est libre de droit 

Jeu programmé par Léo GERLINGER et Olivier GASTON 
Dans le cadre de l'enseignement en Programmation orienté objet de Miranda CONINX
Polytech Sorbonne 2022/2023

Sprites réalisées par Olivier GASTON et trouvés sur spriters-resource.com
Bruitages trouvés sur pixabay.com et modifié par Olivier GASTON
Musique réalisé par Victor FAUCHER 


================Controles================

Tous les controles donné ici seront considéré comme vennant d'un clavier Français


-Menu Pause-

Déplacez vous dans les menu à l'aide des touches z et s de votre clavier.
Validez votre choix à l'aide de la touche e.

Vous pouvez ouvrir le menu pause à tout moment à l'aide du bouton echap. 


-Joueur 1-

Le joueur se déplace à l'aide des touches zqsd de son clavier.
Il effectue une attaque légére mais longue avec j et une attaque courte mais forte avec k.
Il peut effectuer un dash à l'aide de la barre espace.

-Joueur 2-

Le joueur 2 est un drone suivant automatiquement le joueur 1.
Il peut viser et tirer des balles à l'aide du click gauche de la souris. 
Il peut également détruire les balles enemies en leurs tirant dessus.

================Enemies================

Deux enemies sont actuellement disponible dans le jeu.
Il sera simple d'en rajouter d'autres grâce à la classe "Enemies"

-Skeleton Simple-
Il avance et attaque le joueur en lui faisant des dégats de contact

-Skeleton tireur-
Il avance lentement vers le joueur et se téléporte vers lui si celui-ci est trop loin.
Il tire périodiquement des balles vers le joueur.

-Spawnpoint-
Le spawnpoint permet de faire apparaitre des vagues d'ennemis.
Il ne peut pas être détruit mais il indique le lieu d'apparation des ennemis pour le joueur.

Chaque ennemi à une chance de faire tomber un item qui permettra d'augmenter votre vitesse, vos dégats ou votre rapidité de Dash.

================Création de niveaux================

Il est possible de créer un niveau de l'enregistrer à l'aide du mode de jeu correspondant. 
De même, il est possible de le charger afin de le jouer.
N'hésitez pas à coder votre propre niveau dans Venera et l'enregistrer pour pouvoir y jouer plus tard !

================But du jeu================

Le but est de survivre le plus longtemps possible aux vagues d'ennemies que le jeu va vous envoyer.


