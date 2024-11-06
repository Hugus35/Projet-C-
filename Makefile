main : main.cpp Aquarium.o Bestiole.o Gregaire.o Peureuse.o Prevoyante.o Kamikaze.o Factory.o Milieu.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Gregaire.o Peureuse.o Prevoyante.o Kamikaze.o Factory.o Milieu.o -I. -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I. -I/opt/X11/include

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++11  -c Bestiole.cpp -I. -I/opt/X11/include

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I. -I/opt/X11/include

Gregaire.o : Gregaire.h Bestiole.h Gregaire.cpp
	g++ -Wall -std=c++11  -c Gregaire.cpp -I. -I/opt/X11/include

Peureuse.o : Peureuse.h Bestiole.h Peureuse.cpp
	g++ -Wall -std=c++11  -c Peureuse.cpp -I. -I/opt/X11/include

Prevoyante.o : Prevoyante.h Bestiole.h Prevoyante.cpp
	g++ -Wall -std=c++11  -c Prevoyante.cpp -I. -I/opt/X11/include

Kamikaze.o : Kamikaze.h Bestiole.h Kamikaze.cpp
	g++ -Wall -std=c++11  -c Kamikaze.cpp -I. -I/opt/X11/include

Factory.o : Factory.h Aquarium.h Gregaire.h Peureuse.h Prevoyante.h Kamikaze.h Bestiole.h Factory.cpp
	g++ -Wall -std=c++11  -c Factory.cpp -I. -I/opt/X11/include


clean:
	rm -rf *.o main