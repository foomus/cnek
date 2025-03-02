CC=gcc
CFLAGS=-g -Wall
SDLPATH= -Isrc/SDL2/include -Lsrc/SDL2/lib
LFLAGS= -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 #-mwindows 

BINDIR=./out/bin/
OBJDIR=./out/obj/
WRAPPER=./src/wrapper/

ifdef OS
	OUTPUT=$(BINDIR)main.exe
	CLEAN=del /q out\bin\main.exe out\obj\*.o
else 
	OUTPUT=$(BINDIR)main
	CLEAN=rm -f $(OUTPUT) $(OBJDIR)*.o
endif

OBJS=$(OBJDIR)main.o $(OBJDIR)SDL_Controls.o $(OBJDIR)AssetControls.o $(OBJDIR)errHandler.o $(OBJDIR)timer.o $(OBJDIR)LinkedList.o $(OBJDIR)snek.o $(OBJDIR)apple.o $(OBJDIR)ui.o

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(SDLPATH) $^ $(LFLAGS) -o $@

$(OBJDIR)%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)%.o: $(WRAPPER)%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean: 
	$(CLEAN)