CXXFLAGS = -I../include -Wall -g -std=c++14

libtiny_regex.a: nfa.o dfa.o tiny_regex.o
	ar rv $@ $^

.cpp.o:
	g++ ${CXXFLAGS} -c -o $@ $<

clean:
	rm -rf *.o *.a
