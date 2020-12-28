hashdict: Dictionary.o HashList.o main.o
	g++ -o hashdict Dictionary.o HashList.o main.o -g -std=c++11 
main.o: main.cpp Dictionary.h HashList.h
	g++ -c main.cpp -g -std=c++11 
Dictionary.o: Dictionary.cpp Dictionary.h HashList.h HashList.cpp
	g++ -c Dictionary.cpp -g -std=c++11
HashList.o: HashList.h HashList.cpp
	g++ -c HashList.cpp -g -std=c++11
clean:
	rm -f *.o hashdict
