testpoly: testpoly.o
	g++ -g  $^ -o $@

testpoly.o: testpoly.cpp poly.h
	g++ -g -c  -std=c++11 $< -o $@

.PHONY: clean

clean:
	-rm testpoly.o testpoly
