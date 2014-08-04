ODIR=./obj
BDIR=./bin
SRC=./src

_HEADERS := sdl.h draw.h
_OBJECTS := $(_HEADERS:.h=.o)
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJECTS))
HEADERS = $(patsubst %,$(SRC)/%,$(_HEADERS))
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -luser32 -lgdi32 -lwinmm -ldxguid
INCLUDES := -I. -I$(ODIR)
CFLAGS = -Wall -g -std=c11
#NODEBUG = -O2 -std=c11 -mwindows
CC = gcc

default: Peg

build:
	@test -d $(ODIR) || mkdir $(ODIR)
	@test -d $(BDIR) || mkdir $(BDIR)

check: Peg
	$(BDIR)/Peg

clean:
	rm -rf ../obj/
	rm -rf ../bin/
	rm -f ./*~
	rm -f ./*.swp

rebuild: clean default

Peg: ${OBJECTS} $(SRC)/include.h
	${CC} $^ $(SRC)/main.c $(INCLUDES) $(LIBS) $(CFLAGS) -o $(BDIR)/$@

$(ODIR)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/include.h build
	${CC} $< -c $(CFLAGS) -o $@

.PHONY: default clean check dist distcheck install rebuild uninstall