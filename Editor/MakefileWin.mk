LIBRARY_PATH = ../Framework/Output

CC = g++
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror# -fsanitize=address -g3 -std=c99 -O0
LDLIBS = -lm

OUTPUT = bin

EXEC = $(OUTPUT)/ParticuleEditor.exe

Scrs_dir = srcs libs/DearImGui

SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -I ${LIBRARY_PATH}/includes
LDLIBS += -L${LIBRARY_PATH}/lib -L${LIBRARY_PATH}/lib/PARTICULE -l:particule.a -L ${LIBRARY_PATH}/includes

CFLAGS += -I ${LIBRARY_PATH}/includes/SDL2
LDLIBS += -L${LIBRARY_PATH}/lib/SDL2 -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32

CFLAGS += -I ./includes
LDLIBS += -L ./includes

CFLAGS += -I ./libs
LDLIBS += -L ./libs

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)
	@echo "done !"

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDLIBS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f $(EXEC)

re: clean all