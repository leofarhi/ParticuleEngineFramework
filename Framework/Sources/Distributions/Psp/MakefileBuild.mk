SRCS = $(shell find $(Scrs_dir) -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

PSP_LIBS = -lpspgum -lpspgu -lm -lpspaudio -lpspmp3 -lpspaudiocodec -lpspaudiolib -lpspsdk -lpsprtc -lpsputility

CFLAGS:=$(filter-out -Werror,$(CFLAGS))
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti

INCDIR = ./includes
LIBS = $(PSP_LIBS)

TARGET_LIB = particule.a


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
	echo $(SRCS)