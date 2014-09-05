# Where to find libraries and source directories
LFLAGS = -L./Libraries/TinyXML/lib -Wl,-rpath=./Libraries/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -ltinyxml
IFLAGS = -I./Libraries/TinyXML/include -I./Libraries/FastDelegate/include
SRCDIR = Src ../Tetris/Src/Event ../Tetris/Src/Event/Events ../Tetris/Src/GameState ../Tetris/Src/GameApp ../Tetris/Src/Graphics ../Tetris/Src/Resource ../Tetris/Src/Process ../Tetris/Src/Process/Processes ../Tetris/Src/TetrisLogic ../Tetris/Src/Network

# Lists of .cpp, .o and .d files
SRCLIST = $(foreach DIR, $(SRCDIR), $(patsubst $(DIR)/%.cpp, %.cpp, $(wildcard $(DIR)/*.cpp)))
OBJLIST = $(patsubst %.cpp, %.o, $(SRCLIST))
DEPLIST = $(patsubst %.cpp, Temp/%.d, $(SRCLIST))

# Enable Release or Debug mode
ifeq "$(MODE)" "RELEASE"
	CFLAGS = $(IFLAGS)
	VAR = RELEASE
	EXEC = Release/TetrisAI
else
	CFLAGS = -Wall -g $(IFLAGS)
	VAR = DEBUG
	EXEC = Debug/TetrisAI
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
	@sed -i -e 's/^/../' $(patsubst %.o, %.d, $@) 
	@mv $@ Temp
	@mv $(patsubst %.o, %.d, $@) Temp

.PHONY : clean documentation

# Create folders
folders :
	@mkdir -p Debug
	@mkdir -p Release
	@mkdir -p Temp

# Clean Temp directory
clean :
	@rm -rf Temp
	@rm -rf Doc
	@rm -rf Debug
	@rm -rf Release
	@echo "Cleaned project"

# Generate documentation
documentation :
	@echo "Generating documentation"
	@doxygen Doxyfile
