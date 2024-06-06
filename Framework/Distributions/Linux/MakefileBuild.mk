CC = g++
CFLAGS = -MMD
CFLAGS = #-Wall -Wextra #-fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = -lm
OUTPUT = .

NAME = particule.a

Scrs_dir = ./srcs

#cherche les fichiers .cpp dans les dossiers et les sous-dossiers recursivement
SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDLIBS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

CFLAGS += -I ./includes
LDLIBS += -L ./includes

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(OUTPUT)/$(NAME) $(OBJS)

#regle pour les fichiers .o
%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDLIBS) -c $< -o $@


-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

re: clean all

.PHONY: all clean re