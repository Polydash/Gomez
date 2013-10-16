LFLAGS = -L./Libraries/SDL/lib -L./Libraries/TinyXML/lib -lSDL -lSDLmain -ltinyxml
IFLAGS = -I./Libraries/SDL/include -I./Libraries/TinyXML/include -I./Libraries/FastDelegate/include

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

main : TetrisMain.o SDLApp.o GameStateManager.o EventManager.o
	g++ -o $(EXEC) $^ $(LFLAGS)
	mv *.o Temp

TetrisMain.o : TetrisMain.cpp TetrisStd.h SDLApp.h
SDLApp.o : SDLApp.cpp SDLApp.h TetrisStd.h GameStateManager.h EventManager.h
GameStateManager.o : GameStateManager.cpp GameStateManager.h IGameState.h
EventManager.o : EventManager.cpp EventManager.h IEvent.h

%.o : %.cpp
	g++ -c $< $(CFLAGS) -D$(VAR)

.PHONY : clean leakcheck

clean :
	rm Temp/*.o
	
leakcheck :
	valgrind --suppressions=./SDLleaks.supp --leak-check=full Debug/Tetris
