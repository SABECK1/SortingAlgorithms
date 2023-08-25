all:
	g++ -Isrc/Include -Lsrc/lib -g -o main main.cpp -lmingw32 -lSDL2main -lSDL2 
