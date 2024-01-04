all: obj lab-08_shared-ptr
obj/shared_ptr.o:
	g++ -c src/shared_ptr.cpp -I include -o obj/shared_ptr.o
obj/matrix.o:
	g++ -c src/matrix.cpp -I include -o obj/matrix.o
obj/main.o:
	g++ -c src/main.cpp -I include -o obj/main.o
lab-08_shared-ptr: obj/shared_ptr.o obj/matrix.o obj/main.o
	g++ obj/shared_ptr.o obj/matrix.o obj/main.o -o lab-08_shared-ptr
obj:
	mkdir obj
clean:
	rm -rf *.o obj