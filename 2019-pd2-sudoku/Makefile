transform generate solve: sudoku.o transform.o generate.o solve.o
	g++ -o transform transform.o sudoku.o
	g++ -o generate generate.o sudoku.o
	g++ -o solve solve.o sudoku.o
sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp
transform.o generate.o solve.o: transform.cpp generate.cpp solve.cpp sudoku.h
	g++ -c transform.cpp
	g++ -c generate.cpp
	g++ -c solve.cpp
clean:
	rm *.o
