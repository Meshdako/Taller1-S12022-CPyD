output: main_openmp.o
	g++ -fopenmp -lm main_openmp.o -o paralelo 

main_openmp.o: main_openmp.cpp
	g++ -c main_openmp.cpp

clean:
	rm *.o paralelo