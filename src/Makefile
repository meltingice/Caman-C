OBJ = caman-cli.o caman.o filters.o render.o
PRGNAME = caman-cli

# Colors
CCCOLOR="\033[34m"
LINKCOLOR="\033[34;1m"
SRCCOLOR="\033[33m"
BINCOLOR="\033[37;1m"
MAKECOLOR="\033[32;1m"
ENDCOLOR="\033[0m"

QUIET_CC = @printf '    %b %b\n' $(CCCOLOR)CC$(ENDCOLOR) $(SRCCOLOR)$@$(ENDCOLOR);
QUIET_LINK = @printf '    %b %b\n' $(LINKCOLOR)LINK$(ENDCOLOR) $(BINCOLOR)$@$(ENDCOLOR);

OPTIMIZATION?=-O2
CFLAGS?=-std=c99 -pedantic $(OPTIMIZATION) -Wall -W $(ARCH) $(PROF)
CCLINK?=-lm -pthread
CCOPT= $(CFLAGS) $(ARCH) $(PROF)

all: caman-cli
	cp caman-cli ../bin/

# Deps (generated with `make dep`)
caman-cli.o: caman-cli.c caman.h filters.h render.h
caman.o: caman.c caman.h filters.h render.h
filters.o: filters.c caman.h filters.h render.h
render.o: render.c caman.h filters.h render.h

dep:
	$(CC) -MM *.c
	
caman-cli: $(OBJ)
	$(QUIET_LINK)$(CC) `Wand-config --ldflags --libs` -o $(PRGNAME) $(CCOPT) $(OBJ) $(CCLINK)
	
caman-cli.o: caman-cli.c
	$(QUIET_CC)$(CC) `Wand-config --cflags --cppflags` -c $(CFLAGS) $(COMPILE_TIME) $<

caman.o: caman.c
	$(QUIET_CC)$(CC) `Wand-config --cflags --cppflags` -c $(CFLAGS) $(COMPILE_TIME) $<

filters.o: filters.c
	$(QUIET_CC)$(CC) `Wand-config --cflags --cppflags` -c $(CFLAGS) $(COMPILE_TIME) $<

render.o: render.c
	$(QUIET_CC)$(CC) `Wand-config --cflags --cppflags` -c $(CFLAGS) $(COMPILE_TIME) $<
	
clean:
	rm *.o caman-cli