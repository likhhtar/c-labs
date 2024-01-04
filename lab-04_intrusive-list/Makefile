all: obj lab-04_intrusive-list

obj/clist.o:
	gcc -c src/clist.c -I include -o obj/clist.o
obj/main.o:
	gcc -c src/main.c -I include -o obj/main.o
lab-04_intrusive-list: obj/clist.o obj/main.o
	gcc obj/clist.o obj/main.o -o lab-04_intrusive-list
obj:
	mkdir obj
clean:
	rm -rf *.o obj

