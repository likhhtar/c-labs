all: obj lab-07_matrix
obj/matrix.o:
	g++ -c src/matrix.cpp -I include -o obj/matrix.o
obj/main.o:
	g++ -c src/main.cpp -I include -o obj/main.o
lab-07_matrix: obj/matrix.o obj/main.o
	g++ obj/matrix.o obj/main.o -o lab-07_matrix
obj:
	mkdir obj
clean:
	rm -rf *.o obj
