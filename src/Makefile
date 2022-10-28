build: compile link
all: compile link run

compile: 
	g++ -c *.cpp -I"C:\Users\84948\Documents\libaries\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ *.o -o main -L"C:\Users\84948\Documents\libaries\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

run:
	./main

clean:
	rm -f *.o 