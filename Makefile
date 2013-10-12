LFLAGS = -L./Libraries/SDL/lib -L./Libraries/TinyXML/lib -lSDL -lSDLmain -ltinyxml
IFLAGS = -I./Libraries/SDL/include -I./Libraries/TinyXML/include

ifeq "$(MODE)" "RELEASE"
	CFLAGS = $(IFLAGS)
	VAR = RELEASE
	EXEC = Release/Tetris
else
	CFLAGS = -Wall -g $(IFLAGS)
	VAR = DEBUG
	EXEC = Debug/Tetris
endif

vpath %.cpp Src
vpath %.h Src

all : main

main : TetrisMain.o SDLApp.o GameStateManager.o
	g++ -o $(EXEC) $^ $(LFLAGS)
	mv *.o Temp

TetrisMain.o : TetrisMain.cpp TetrisStd.h SDLApp.h
SDLApp.o : SDLApp.cpp SDLApp.h TetrisStd.h GameStateManager.h
GameStateManager.o : GameStateManager.cpp GameStateManager.h IGameState.h

%.o : %.cpp
	g++ -c $< $(CFLAGS) -D$(VAR)

.PHONY : clean

clean :
	rm Temp/*.o
