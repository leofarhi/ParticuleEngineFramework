CC = g++
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra #-fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = -lm
OUTPUT = ../bin
BUILD =	../build

NAME = Particule.a

Scrs_dir = ../Particule ./Particule

#cherche les fichiers .cpp dans les dossiers et les sous-dossiers recursivement
SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

#remplace les .cpp par .o et les place dans le dossier build
OBJS = $(SRCS:%.cpp=$(BUILD)/%.o)
#remplace les .cpp par .d et les place dans le dossier build
DEPS = $(OBJS:.o=.d)

CFLAGS += -I SDL2/SDL2_WIN_Include/include -I ../Particule/includes -I ./Particule/includes
LDLIBS += -L SDL2/SDL2_WIN_Include/lib -L ../Particule/includes -L ./Particule/includes -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32

all: $(OUTPUT)/$(NAME)
	ar rcs $(OUTPUT)/$(NAME) $(OBJS)
	mkdir -p $(OUTPUT)/exedir
	cp -r BIN_SDL/* $(OUTPUT)/exedir
	mkdir -p $(OUTPUT)/includes
	cp -r ../Particule/includes/* $(OUTPUT)/includes
	cp -r ./Particule/includes/* $(OUTPUT)/includes
	mkdir -p $(OUTPUT)/SDL2/include
	mkdir -p $(OUTPUT)/SDL2/lib
	cp -r SDL2/SDL2_WIN_Include/include/* $(OUTPUT)/SDL2/include
	cp -r SDL2/SDL2_WIN_Include/lib/* $(OUTPUT)/SDL2/lib

$(OUTPUT)/$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)
	rm -rf $(OUTPUT)
	rm -f $(NAME)

re: clean all

.PHONY: all clean re