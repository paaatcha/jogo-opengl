all: trab2		

trab2:	game.cpp
		g++ game.cpp gameFuncs.cpp -o game -lGL -lglut -lGLU -lm -lfreeimage
		
clean: 
		rm -rf game

remade:
		$(MAKE) clean
		$(MAKE)
