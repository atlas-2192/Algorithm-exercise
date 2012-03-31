sortobj = sort.o mylib.o
packobj = pack.o mylib.o

$(packobj): mylib.h
$(sortobj): mylib.h

all: sort pack

sort: $(sortobj)
	gcc -o sort $(sortobj)

pack: $(packobj)
	gcc -o pack $(packobj)

.PHONY: clean	
clean:
	-rm *.o sort pack
