LIBRARY_PATH = ../Framework/Output

CC = g++
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror# -fsanitize=address -g3 -std=c99 -O0
LDLIBS = -lm

OUTPUT = bin
BUILD_DIR = build

EXEC = $(OUTPUT)/ParticuleEditor.exe

Scrs_dir = srcs

SRCS = $(shell find $(Scrs_dir) -name "*.cpp") $(shell find $(Scrs_dir) -name "*.c")

OBJS = $(patsubst $(Scrs_dir)/%, $(BUILD_DIR)/%, $(SRCS:.cpp=.o))
OBJS := $(patsubst $(Scrs_dir)/%, $(BUILD_DIR)/%, $(OBJS:.c=.o))
DEPS = $(OBJS:.o=.d)

CFLAGS += -I ${LIBRARY_PATH}/includes
LDLIBS += -L${LIBRARY_PATH}/lib -L${LIBRARY_PATH}/lib/PARTICULE -l:particule.a -L ${LIBRARY_PATH}/includes

CFLAGS += -I ${LIBRARY_PATH}/includes/SDL2
LDLIBS += -L${LIBRARY_PATH}/lib/SDL2 -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32

CFLAGS += -I ./includes
LDLIBS += -L ./includes

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)
	@echo "done !"

$(BUILD_DIR)/%.o: $(Scrs_dir)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(Scrs_dir)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f $(EXEC)

re: clean all

.PHONY: all clean re