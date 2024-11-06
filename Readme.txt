Le projet a pour but de simuler le cycle de vie d'un écosysteme composé de diverses bestioles au comportement et caractéristiques  différents.

Le code permettant cette simulation a été implémenté à travers différents fichiers, utilisant le language C++.

Avant d'exécuter le projet, il est nécessaire d'installer Xcode. 
Pour cela, si vous êtes sur Mac, ouvrez un terminal et tapez :
>> Xcode-select --install
>> xcode_select -p
>> g++ --version pour vérifier l'installation.

Si vous êtes sur Linux :
sudo apt-get install g++

Afin de faciliter la compilation, un fichier makefile se trouve dans le dossier du projet, permettant de lier les fichiers entre eux et de compiler le tout.
Pour l'exécuter, il faut se placer dans le dossier dans lequel le projet est enregistré via un terminal.
Ensuite, il suffit de lancer successivement les commandes suivantes :
>> make clean
>> make
>> ./main

Ce programme lance une simulation de quelques dizaines de seconde, dans lequel les bestioles évoluent en bougeant, se rencontrant, se clonant, et mourant.
Chaque espèce de bestiole a une couleur différente, ce qui permet de les différencier.
L'interface peut être quitté via la touche "echap", ou s'arrête lorsque la simulation est terminée.
Le nombre de mort ayant survenu au cours de cette simulation est affiché dans le terminal.


Des tests ont également été livrés avec le projet (via le fichier test.cpp) afin de vérifier le bon fonctionnement de certaines fonctionnalités.
Ces derniers sont visuels, ils permettent une première approche lors de la vérification de certaines fonctionnalités.

Pour les lancer, il faut dans un premier temps appeler les commandes suivantes afin de compiler le code : 
>>make clean
>>make

Puis celles-ci afin de compiler puis exécuter le fichier test : 
>> g++ -Wall -std=c++11 -o test test.cpp Aquarium.o Bestiole.o Gregaire.o Peureuse.o Prevoyante.o Kamikaze.o Factory.o Milieu.o -I. -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread
>> ./test

Les tests se lancent successivement, le terminal affiche quelle fonctionnalité va être testée dans la simulation qui suit.