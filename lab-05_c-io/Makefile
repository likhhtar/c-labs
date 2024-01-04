all: obj lab-05_c-io

obj/clist.o:
	gcc -c src/clist.c -I include -o obj/clist.o
obj/main.o:
	gcc -c src/main.c -I include -o obj/main.o
obj/point_list.o:
	gcc -c src/point_list.c -I include -o obj/point_list.o
lab-05_c-io: obj/clist.o obj/main.o obj/point_list.o
	gcc obj/clist.o obj/point_list.o obj/main.o -o lab-05_c-io
obj:
	mkdir obj
clean:
	rm -rf *.o obj



