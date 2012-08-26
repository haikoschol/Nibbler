#
# Makefile created by mfg (version 2.3)
#

TARGET =	Nibbler
HEADERS =	Item.h Nibbler.h Sprite.h Timer.h
SOURCES =	Item.cpp Nibbler.cpp Sprite.cpp Timer.cpp main.cpp
OBJECTS =	Item.o Nibbler.o Sprite.o Timer.o main.o
CLEAN =		Item.o Nibbler.o Sprite.o Timer.o main.o

#>		--- do not remove this line ---
AR =		ar
ARFLAGS =	cr
CC =		g++
CFLAGS =	-Wall -g $(shell sdl-config --cflags)
CPPFLAGS =
DEFS =
DISTCLEAN =
EXEEXT =
INCLUDES =
INSTALL =	install -c
INSTALL_DATA =	$(INSTALL) -m 644
INSTALL_PROGRAM =	$(INSTALL) -s
LDFLAGS =
LEX =		lex
LIBS =		$(shell sdl-config --libs) -lSDL_image # -lm -lobjc
LIBTOOL =	libtool $(LTFLAGS)
LPR =		lpr -h
PROGRAMS =	$(OBJECTS:.o= )
RANLIB =	ranlib
RM =		rm -f
VERSION =	0
YACC =		yacc

prefix =	/usr/local
bindir =	$(prefix)/bin
libdir =	$(prefix)/lib
mandir =	$(prefix)/man

COMPILE =	$(CC) -c $(CFLAGS) $(DEFS) $(INCLUDES) $(CPPFLAGS)

.SUFFIXES:	.l .y .m .cc .cpp
.c.o:
		$(COMPILE) $< -o $@
.m.o:
		$(COMPILE) $< -o $@
.cc.o:
		$(COMPILE) $< -o $@
.cpp.o:
		$(COMPILE) $< -o $@
.l.c:
		$(LEX) $(LFLAGS) -t $< >$@
.y.c:
		$(YACC) $(YFLAGS) -d $<
		mv y.tab.c $*.c
		cmp -s y.tab.h $*.h || cp y.tab.h $*.h
.y.h:
		$(YACC) $(YFLAGS) -d $<
		mv y.tab.c $*.c
		cmp -s y.tab.h $*.h || cp y.tab.h $*.h

SHELL =		/bin/sh

$(TARGET):	$(OBJECTS) $(ADDLIBS)
		$(CC) $(LDFLAGS) $(OBJECTS) $(ADDLIBS) $(LIBS) -o $@

check:		$(TARGET)

clean:
		$(RM) $(CLEAN) $(TARGET) $(TARGET)$(EXEEXT) core

distclean:	clean
		$(RM) $(DISTCLEAN)

print:
		$(LPR) $(HEADERS) $(SOURCES)

install:	$(TARGET)
		$(INSTALL) -d $(bindir)
		$(INSTALL_PROGRAM) $(TARGET)$(EXEEXT) $(bindir)

uninstall:
		$(RM) $(bindir)/$(TARGET)$(EXEEXT)

#>		--- do not remove this line ---

Force_Update:

Item.o:	Item.cpp Item.h Sprite.h

Nibbler.o:	Nibbler.cpp Item.h Nibbler.h Sprite.h Timer.h

Sprite.o:	Sprite.cpp Sprite.h

Timer.o:	Timer.cpp Timer.h

main.o:	main.cpp Item.h Nibbler.h Sprite.h Timer.h
