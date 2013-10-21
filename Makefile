# Where to find libraries and source directories
LFLAGS = -L./Libraries/SDL/lib -L./Libraries/TinyXML/lib -Wl,-rpath=./Libraries/SDL/lib -lSDL -lSDLmain -lSDL_image -ltinyxml
IFLAGS = -I./Libraries/SDL/include -I./Libraries/TinyXML/include -I./Libraries/FastDelegate/include
SRCDIR = Src Src/Event Src/GameState Src/GameApp Src/Graphics Src/Resource

# Lists of .cpp, .o and .d files
SRCLIST = $(foreach DIR, $(SRCDIR), $(patsubst $(DIR)/%.cpp, %.cpp, $(wildcard $(DIR)/*.cpp)))
OBJLIST = $(patsubst %.cpp, %.o, $(SRCLIST))
DEPLIST = $(patsubst %.cpp, Temp/%.d, $(SRCLIST))

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

all : folders $(EXEC)

# Link
$(EXEC) : $(OBJLIST)  
		@echo "Building  : $(EXEC)"
		@g++ -o $(EXEC) $(patsubst %.o, Temp/%.o, $(OBJLIST)) $(LFLAGS)

# Include dependencies
-include $(DEPLIST)

# Compile and generate dependencies
%.o : %.cpp
	@echo "Compiling : $<"
	@g++ -c $< $(CFLAGS) -D$(VAR)
	@g++ $(CFLAGS) -MM -MT $@ $< -MF $(patsubst %.o, %.d, $@)
	@sed -i -e 's/Src/..\/Src/g' $(patsubst %.o, %.d, $@) 
	@mv $@ Temp
	@mv $(patsubst %.o, %.d, $@) Temp

.PHONY : clean leakcheck

# Create folders
folders :
	@mkdir -p Debug
	@mkdir -p Release
	@mkdir -p Temp

# Clean Temp directory
clean :
	@rm Temp/*.o
	@rm Temp/*.d
	@echo "Cleaned \"Temp\" directory"

# Execute Debug mode with leak check
leakcheck :
	valgrind --suppressions=./Data/SDLleaks.supp --leak-check=full Debug/Tetris
