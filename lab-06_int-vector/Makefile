all: obj lab-06_int-vector
obj/my_vector.o:
	g++ -c src/my_vector.cpp -I include -o obj/my_vector.o
obj/main.o:
	g++ -c src/main.cpp -I include -o obj/main.o
lab-06_int-vector: obj/my_vector.o obj/main.o
	g++ obj/my_vector.o obj/main.o -o lab-06_int-vector
obj:
	mkdir obj
clean:
	rm -rf *.o obj