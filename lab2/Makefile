lab2: lab2class.o main.o
	g++ -o lab2 main.o lab2class.o

lab2class.o: lab2class.cpp lab2class.h
	g++ -c lab2class.cpp

main.o: main.cpp lab2class.h
	g++ -c main.cpp

clean:
	rm  lab2 *.o
