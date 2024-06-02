
CFLAGS += -I $(ParticuleBinDir)/includes
LDLIBS += -L$(ParticuleBinDir) -l:particule.a -L $(ParticuleBinDir)/includes

CFLAGS += -I $(ParticuleBinDir)/includes/SDL2/include
LDLIBS += -L $(ParticuleBinDir)/includes/SDL2/lib -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype -lcomdlg32
