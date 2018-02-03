CXXFLAGS = -Iinclude -Wall -g -std=c++14
LDFLAGS = -Lsrc -ltiny_regex

main: main.o libtiny_regex.a
	g++ ${CXXFLAGS} -o $@ $< ${LDFLAGS}

libtiny_regex.a:
	cd src; make $@; cd ..

.cpp.o:
	g++ ${CXXFLAGS} -c -o $@ $<

clean:
	cd src; make $@; cd ..
	rm -rf main main.o
