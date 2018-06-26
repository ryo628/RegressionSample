kadai3:	kadai3.o Food.o Regression.o
	g++ -o kadai3 kadai3.o Food.o Regression.o

kadai3.o: kadai3.cpp
	g++ -c kadai3.cpp

Food.o: Food.cpp
	g++ -c Food.cpp

Regression.o: Regression.cpp
	g++ -c Regression.cpp

clean:
	rm -f *.o kadai3