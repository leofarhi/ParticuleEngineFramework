LIBRARY_PATH = ../Framework/Output

CC = g++
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra -Werror # -fsanitize=address -g3 -std=c99 -O0
LDLIBS = -lm

OUTPUT = bin
EXEC = $(OUTPUT)/ParticuleEditor
Scrs_dir = srcs libs/DearImGui

# Find all .cpp files in the src directory
SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

# Generate .o and .d file names from .cpp source files
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)



# Include paths
CFLAGS += -I ${LIBRARY_PATH}/includes

# Library paths and linking
LDLIBS += -L${LIBRARY_PATH}/lib -L${LIBRARY_PATH}/lib/PARTICULE -l:particule.a
CFLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDLIBS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

CFLAGS += -I ./includes
LDLIBS += -L ./includes

CFLAGS += -I ./libs
LDLIBS += -L ./libs

# Default target
#all: $(EXEC)

# Linking
$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(EXEC) $(OBJS) $(LDLIBS)
	@echo "main done!"

# Compilation
%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDLIBS) -c $< -o $@

$(foreach f, $(EXE), $(eval $(f):))
# Include dependency files
-include $(DEPS)

# Clean target
clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f $(EXEC)

# Rebuild target
re: clean all