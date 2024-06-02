CC = g++
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror# -fsanitize=address -g3 -std=c99 -O0
LDLIBS = -lm

OUTPUT = bin

EXEC = $(OUTPUT)/main.exe

Scrs_dir = src

SRCS = $(shell find $(Scrs_dir) -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += -I includes

ParticuleBinDir := ../bin

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(OUTPUT)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)
	cp -r $(ParticuleBinDir)/exedir/* $(OUTPUT)
	@echo "main.exe done !"

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -rf $(OUTPUT)

include $(ParticuleBinDir)/Particule.mk

re: clean all