all: compile link run

compile:
	g++ -I"C:\SFML-2.6.2\include" -I"C:\SFML-2.6.2\include" -c test.cpp -o test.o -O2

link: 
	g++ -I"C:\SFML-2.6.2\include" .\test.o -o test.exe -L"C:\SFML-2.6.2\lib" -lmingw32 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -O2

run:
	./test.exe