output: main.o Compressor.o Image.o Menu.o
	g++ main.o Compressor.o Image.o Menu.o -o output

main.o: main.cpp
	g++ -c main.cpp

Compressor.o: Compressor.cpp Compressor.h
	g++ -c Compressor.cpp

Image.o: Image.cpp Image.h
	g++ -c Image.cpp

Menu.o: Menu.cpp Menu.h
	g++ -c Menu.cpp

clean:
	rm *.o output