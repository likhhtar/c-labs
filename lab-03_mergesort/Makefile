all: obj lab-03_mergesort

obj/mergesort.o:
	gcc -c src/mergesort.c -I include -o obj/mergesort.o
obj/main.o:
	gcc -c src/main.c -I include -o obj/main.o
lab-03_mergesort: obj/mergesort.o obj/main.o
	gcc obj/mergesort.o obj/main.o -o lab-03_mergesort
obj:
	mkdir obj
clean:
	rm -rf *.o obj

