ifneq ($(MAKECMDGOALS), clean)
ifndef LIBRARY_PATH
$(error LIBRARY_PATH n'est pas défini)
endif
endif

CC = g++
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra -Werror # -fsanitize=address -g3 -std=c99 -O0
LDLIBS = -lm

OUTPUT = bin
EXEC = $(OUTPUT)/main
Scrs_dir = src

# Find all .cpp files in the src directory
SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

# Generate .o and .d file names from .cpp source files
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)



# Include paths
CFLAGS += -I includes
CFLAGS += -I ${LIBRARY_PATH}/includes

# Library paths and linking
LDLIBS += -L${LIBRARY_PATH}/lib -L${LIBRARY_PATH}/lib/PARTICULE -l:particule.a
CFLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDLIBS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

# Default target
#all: $(EXEC)

# Linking
$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(EXEC) $(OBJS) $(LDLIBS)
	@echo "main done!"

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