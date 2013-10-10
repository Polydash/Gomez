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

main : TetrisMain.o TetrisApp.o
	g++ -o $(EXEC) $^ $(LFLAGS)
	mv *.o Temp

TetrisMain.o : TetrisMain.cpp TetrisStd.h TetrisApp.h
TetrisApp.o : TetrisApp.cpp TetrisApp.h TetrisStd.h

%.o : %.cpp
	g++ -c $< $(CFLAGS) -D$(VAR)

.PHONY : clean

clean :
	rm Temp/*.o
