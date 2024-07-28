ifneq ($(MAKECMDGOALS), clean)
ifndef LIBRARY_PATH
$(error LIBRARY_PATH n'est pas défini)
endif
endif

CC = g++
CPPFLAGS = -MMD
CFLAGS =# -Wall -Wextra -Werror # -fsanitize=address -g3 -std=c99 -O0
LDLIBS = -lm

OUTPUT = bin
BUILD_DIR = build

EXEC = $(OUTPUT)/main

Scrs_dir = ../srcs .

SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

# Change SRCS to a list of relative paths from the source directories
REL_SRCS = $(subst $(shell pwd)/,,$(SRCS))

# Change object files and dependency files to be in BUILD_DIR with corresponding directories
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(REL_SRCS))
DEPS = $(OBJS:.o=.d)

CFLAGS += -I ../includes -I ./
CFLAGS += -I ${LIBRARY_PATH}/includes
LDLIBS += -L${LIBRARY_PATH}/lib -L${LIBRARY_PATH}/lib/PARTICULE -l:particule.a
CFLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDLIBS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)
	@echo "done !"

# Pattern rule for object files
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDLIBS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXEC)

re: clean all
