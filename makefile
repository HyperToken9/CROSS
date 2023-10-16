final: cros-core.c build/master.o
	gcc -o cros-core.o cros-core.c build/master.o
build/master.o: cross/master/master.c cross/master/master.h
	gcc -o build/master.o -c cross/master/master.c 