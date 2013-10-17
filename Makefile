# Where to find libraries and source directories
LFLAGS = -L./Libraries/SDL/lib -L./Libraries/TinyXML/lib -Wl,-rpath=./Libraries/SDL/lib -lSDL -lSDLmain -lSDL_image -ltinyxml
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
vpath %.o Temp/

all : $(EXEC)

# Linking
$(EXEC) : $(OBJLIST)
		@echo "Building  : $(EXEC)"
		@g++ -o $(EXEC) $(patsubst %.o, Temp/%.o, $^) $(LFLAGS)

# Dependencies
TetrisMain.o : GameStd.h SDLApp.h
SDLApp.o : SDLApp.h GameStd.h GameStateManager.h EventManager.h
GameStateManager.o : GameStateManager.h GameStd.h IGameState.h MenuState.h IntroState.h EventManager.h Events.h
IntroState.o : IntroState.h SDLApp.h Events.h IGameState.h
MenuState.o : MenuState.h SDLApp.h Events.h IGameState.h
EventManager.o : EventManager.h IEvent.h
GfxResource.o : GfxResource.h
GfxResImage.o : GfxResImage.h GfxResource.h

# Compiling
%.o : %.cpp
	@echo "Compiling : $<"
	@g++ -c $< $(CFLAGS) -D$(VAR)
	@mv $@ Temp

.PHONY : clean leakcheck

# Remove .o files
clean :
	@rm Temp/*.o
	@echo "Cleaned \"Temp\" directory"

# Execute Debug mode with leak check
leakcheck :
	valgrind --suppressions=./SDLleaks.supp --leak-check=full Debug/Tetris
