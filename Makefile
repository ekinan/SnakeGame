.SUFFIXES:	.c
.PHONY:		clean

create:
	-rm *.h.gch
	gcc -pthread *.c

clean:
	-rm *.h.gch
