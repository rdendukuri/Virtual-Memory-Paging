
CFLAGS+=-O
CFLAGS+=-Wall -Werror
#CFLAGS+=-Wno-unused-function

LDFLAGS+=-lm

.PHONY: all clean world

all:: Assign6

Assign6: Assign6.o
	$(LINK.cpp) -o $@ $^

clean::
	rm -f *.o Assign6

world:: clean all

Assign6.o:: Assign6.cpp Assign6.h


