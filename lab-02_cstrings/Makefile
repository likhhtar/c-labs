all: obj lab-02_cstrings

obj/test.o:
	gcc -c src/test.c -I include -o obj/test.o
obj/str.o:
	gcc -c src/str.c -I include -o obj/str.o
obj/test_str.o:
	gcc -c src/test_str.c -I include -o obj/test_str.o
lab-02_cstrings: obj/test.o obj/str.o obj/test_str.o
	gcc obj/test.o obj/str.o obj/test_str.o -o lab-02_cstrings
obj:
	mkdir obj
clean:
	rm -rf *.o obj