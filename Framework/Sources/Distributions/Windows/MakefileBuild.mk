CC = g++
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra #-fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = -lm
OUTPUT = .

NAME = particule.a

Scrs_dir = ./srcs

#cherche les fichiers .cpp dans les dossiers et les sous-dossiers recursivement
SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)


CFLAGS += -I ./includes/SDL2 -I ./includes
LDLIBS += -L ./lib/SDL2 -L ./includes -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(OUTPUT)/$(NAME) $(OBJS)

#regle pour les fichiers .o
%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

re: clean all

.PHONY: all clean re