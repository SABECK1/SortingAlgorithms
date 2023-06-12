all:
	g++ -Isrc/Include -Lsrc/lib  -o main main.cpp  -lmingw32 -lSDL2_mixer -lSDL2main -lSDL2 
