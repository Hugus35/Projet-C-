#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Prevoyante.h"
#include "Kamikaze.h"
#include "Factory.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;



   // Interface de test

   void testGregaire(){
      int nbGregaire = 40;
      int nbPeureuse = 0; 
      int nbPrevoyante = 0;
      int nbKamikaze = 0;

      cout << "Nous allons tester l'initialisation des bestioles gregaires" << endl;
      cout << "L'interface doit afficher des bestioles rouges uniquement"<< endl;

      std::this_thread::sleep_for(std::chrono::seconds(3));

      Aquarium* ecosysteme = new Aquarium( 640, 480, 30, 0, 0);
   
      //Construction de la factory nous permettant d'initialiser l'environnement avec les deux fonctions ci-dessous
      Factory* f1 = new Factory(nbGregaire, nbPeureuse, nbPrevoyante, nbKamikaze, 10, 
                              5, 5, 0.1, 0.9, 75, 150, 0.5, 0.95,
                              75, 150, 0.5, 0.9, -10, 10);
      f1->init(*ecosysteme);
      f1->initAccessories(*ecosysteme);

      // Appel de la boucle permettant de modéliser l'évolution des bestioles. A chaque tour, elle simule le comportement de chaque bestiole
      ecosysteme->run(100);


   }

   void testPeureuse(){

      int nbGregaire = 0;
      int nbPeureuse = 40; 
      int nbPrevoyante = 0;
      int nbKamikaze = 0;

      cout << "Nous allons tester l'initialisation des bestioles peureuses" << endl;
      cout << "L'interface doit afficher des bestioles vertes uniquement"<< endl;

      std::this_thread::sleep_for(std::chrono::seconds(3));

      Aquarium* ecosysteme = new Aquarium( 640, 480, 30, 0, 0);
   
      //Construction de la factory nous permettant d'initialiser l'environnement avec les deux fonctions ci-dessous
      Factory* f1 = new Factory(nbGregaire, nbPeureuse, nbPrevoyante, nbKamikaze, 10, 
                              5, 5, 0.1, 0.9, 75, 150, 0.5, 0.95,
                              75, 150, 0.5, 0.9, -10, 10);

      f1->init(*ecosysteme);
      f1->initAccessories(*ecosysteme);

      // Appel de la boucle permettant de modéliser l'évolution des bestioles. A chaque tour, elle simule le comportement de chaque bestiole
      ecosysteme->run(100);

   }

   void testPrevoyante(){

      int nbGregaire = 0;
      int nbPeureuse = 0; 
      int nbPrevoyante = 40;
      int nbKamikaze = 0;

      cout << "Nous allons tester l'initialisation des bestioles prevoyantes" << endl;
      cout << "L'interface doit afficher des bestioles blanches uniquement"<< endl;

      std::this_thread::sleep_for(std::chrono::seconds(3));

      Aquarium* ecosysteme = new Aquarium( 640, 480, 30, 0, 0);
   
      //Construction de la factory nous permettant d'initialiser l'environnement avec les deux fonctions ci-dessous
      Factory* f1 = new Factory(nbGregaire, nbPeureuse, nbPrevoyante, nbKamikaze, 10, 
                              5, 5, 0.1, 0.9, 75, 150, 0.5, 0.95,
                              75, 150, 0.5, 0.9, -10, 10);
                              
      f1->init(*ecosysteme);
      f1->initAccessories(*ecosysteme);

      // Appel de la boucle permettant de modéliser l'évolution des bestioles. A chaque tour, elle simule le comportement de chaque bestiole
      ecosysteme->run(100);

   }

   void testKamikaze(){

      int nbGregaire = 0;
      int nbPeureuse = 0; 
      int nbPrevoyante = 0;
      int nbKamikaze = 40;

      cout << "Nous allons tester l'initialisation des bestioles kamikazes" << endl;
      cout << "L'interface doit afficher des bestioles bleues uniquement"<< endl;

      std::this_thread::sleep_for(std::chrono::seconds(3));

      Aquarium* ecosysteme = new Aquarium( 640, 480, 30, 0, 0);
   
      //Construction de la factory nous permettant d'initialiser l'environnement avec les deux fonctions ci-dessous
      Factory* f1 = new Factory(nbGregaire, nbPeureuse, nbPrevoyante, nbKamikaze, 10, 
                              5, 5, 0.1, 0.9, 75, 150, 0.5, 0.95,
                              75, 150, 0.5, 0.9, -10, 10);
                              
      f1->init(*ecosysteme);
      f1->initAccessories(*ecosysteme);

      // Appel de la boucle permettant de modéliser l'évolution des bestioles. A chaque tour, elle simule le comportement de chaque bestiole
      ecosysteme->run(100);


   }

   void testClonage(){

      double probaClonage = 0.05;
      double probaNaissance = 0;          //Les naissances sont écartées

      cout << "Nous allons tester le fonctionnement du clonage. " << endl;
      cout << "L'interface débute avec 1 bestiole, on vérifie quelle finisse avec plusieurs bestioles. " << endl;

      std::this_thread::sleep_for(std::chrono::seconds(5));

      Aquarium* ecosysteme = new Aquarium( 640, 480, 30, probaNaissance, probaClonage);
   
      //Construction de la factory nous permettant d'initialiser l'environnement avec les deux fonctions ci-dessous
      Factory* f1 = new Factory(1, 0, 0, 0, 10, 
                              5, 5, 0.1, 0.9, 75, 150, 0.5, 0.95,
                              75, 150, 0.5, 0.9, -10, 10);
                              
      f1->init(*ecosysteme);
      f1->initAccessories(*ecosysteme);

      // Appel de la boucle permettant de modéliser l'évolution des bestioles. A chaque tour, elle simule le comportement de chaque bestiole
      ecosysteme->run(500);

      //if (ecosysteme->getMilieu()->getBestioles().size() > 4) {return true; }

   }

int main()
{

   // Appel des fonctions à tester,  Veuillez les appeler ci-dessous
   // Dans le terminal, veuillez exécuter ensuite les commandes suivantes :
   // make clean
   // make
   //g++ -Wall -std=c++11 -o test test.cpp Aquarium.o Bestiole.o Gregaire.o Peureuse.o Prevoyante.o Kamikaze.o Factory.o Milieu.o -I. -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread
   //  ./test

/*
   testGregaire();
   
   // Attendre 5 seconde
   std::this_thread::sleep_for(std::chrono::seconds(5));

   testPeureuse();

   // Attendre 5 seconde
   std::this_thread::sleep_for(std::chrono::seconds(5));

   testPrevoyante();

   // Attendre 5 seconde
   std::this_thread::sleep_for(std::chrono::seconds(5));
   
   testKamikaze();

   // Attendre 5 seconde
   std::this_thread::sleep_for(std::chrono::seconds(5));
   */

   testClonage();

   return 0;

}
