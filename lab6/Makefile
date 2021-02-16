lab6: genMino.o Mino.o MinoI.o MinoJ.o MinoS.o MinoZ.o tetris5.o
	g++ -o lab6 genMino.o Mino.o MinoI.o MinoJ.o MinoS.o MinoZ.o tetris5.o

genMino.o: genMino.cpp genMino.h
	g++ -c genMino.cpp genMino.h

Mino.o: Mino.cpp Mino.h
	g++ -c Mino.cpp Mino.h

MinoI.o: MinoI.cpp MinoI.h
	g++ -c MinoI.cpp MinoI.h

MinoJ.o: MinoJ.cpp MinoJ.h
	g++ -c MinoJ.cpp MinoJ.h

MinoS.o: MinoS.cpp MinoS.h
	g++ -c MinoS.cpp MinoS.h

MinoZ.o: MinoZ.cpp MinoZ.h
	g++ -c MinoZ.cpp MinoZ.h

tetris5.o: tetris5.cpp genMino.h
	g++ -c tetris5.cpp genMino.h

clean:
	rm *.o
