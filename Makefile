CXX=g++

test: vec_test.o getpss.o
	$(CXX) -o $@ $^

vec_test.o: vec_test.cpp
	$(CXX) -c $<

getpss.o: getpss.cpp
	$(CXX) -c $<

clean:
	rm -f test *.o