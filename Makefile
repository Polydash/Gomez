# Where to find libraries and source directories
LFLAGS = -L./Libraries/SDL/lib -L./Libraries/TinyXML/lib -lSDL -lSDLmain -lSDL_image -ltinyxml
IFLAGS = -I./Libraries/SDL/include -I./Libraries/TinyXML/include -I./Libraries/FastDelegate/include
SRCDIR = Src Src/Event Src/GameState Src/GameApp Src/Graphics

# List of .o files to generate
OBJLIST = $(foreach DIR, $(SRCDIR), $(patsubst $(DIR)/%.cpp, %.o, $(wildcard $(DIR)/*.cpp)))

# Enable Release or Debug mode
ifeq "$(MODE)" "RELEASE"
	CFLAGS = $(IFLAGS)
	VAR = RELEASE
	EXEC = Release/Tetris
else
	CFLAGS = -Wall -g $(IFLAGS)
	VAR = DEBUG
	EXEC = Debug/Tetris
endif

# Replace file names with correct path
vpath %.cpp $(SRCDIR)
vpath %.h $(SRCDIR)

all : main

# Linking
main : $(OBJLIST)
	g++ -o $(EXEC) $^ $(LFLAGS)
	mv *.o Temp

# Dependencies
TetrisMain.o : TetrisMain.cpp GameStd.h SDLApp.h
SDLApp.o : SDLApp.cpp SDLApp.h GameStd.h GameStateManager.h EventManager.h
GameStateManager.o : GameStateManager.cpp GameStateManager.h IGameState.h
EventManager.o : EventManager.cpp EventManager.h IEvent.h
GfxResource.o : GfxResource.cpp GfxResource.h
GfxResImage.o : GfxResImage.cpp GfxResImage.h GfxResource.h

# Compiling
%.o : %.cpp
	g++ -c $< $(CFLAGS) -D$(VAR)

.PHONY : clean leakcheck

# Remove .o files
clean :
	rm Temp/*.o

# Execute Debug mode with leak check
leakcheck :
	valgrind --suppressions=./SDLleaks.supp --leak-check=full Debug/Tetris
