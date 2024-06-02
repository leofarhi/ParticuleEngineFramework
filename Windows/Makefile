CC = g++
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra #-fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = -lm
OUTPUT = ../bin

NAME = particule.a

Scrs_dir = ../Particule ./Particule

#cherche les fichiers .cpp dans les dossiers et les sous-dossiers recursivement
SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)


CFLAGS += -I SDL2/SDL2_WIN_Include/include -I $(OUTPUT)/includes
LDLIBS += -L SDL2/SDL2_WIN_Include/lib -L $(OUTPUT)/includes -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32

all: $(NAME)

$(NAME): $(OBJS)
	mkdir -p $(OUTPUT)
	ar rcs $(OUTPUT)/$(NAME) $(OBJS)
	mkdir -p $(OUTPUT)/exedir
	cp -r SDL2/BIN_SDL/* $(OUTPUT)/exedir
	@echo "Particule.a done !"

#regle pour les fichiers .o
%.o: %.cpp $(OUTPUT)/includes
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OUTPUT)/includes:
	mkdir -p $(OUTPUT)/includes
	cp -r ../Particule/includes/* $(OUTPUT)/includes
	cp -r ./Particule/includes/* $(OUTPUT)/includes
	mkdir -p $(OUTPUT)/includes/SDL2
	cp -r SDL2/SDL2_WIN_Include/* $(OUTPUT)/includes/SDL2
	cp -r Particule.mk $(OUTPUT)

-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -rf $(OUTPUT)
	rm -f $(NAME)

re: clean all

.PHONY: all clean re