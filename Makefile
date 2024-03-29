all:
	-mkdir -r build/obj
	cd src && make
	cd src && make clean

doxygen:
	-mkdir doc
	cd src && make clean
	doxygen src/Doxyfile.in

run: all
	./build/pacman

clean:
	-rm build/pacman
	-cd src && make clean
	-rm obj/*

cmake:
	-mkdir build
	-cd build && cmake .. && make
