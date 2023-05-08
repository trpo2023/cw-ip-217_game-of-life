all: compile link

compile:
	g++ -I "C:\SFML-2.5.1\include" -c ht.cpp

link:
	g++ ht.o -o z -L "C:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o ht
	rm -rf *.exe z