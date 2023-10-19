final: cros-core sample-publisher

cros-core: cros-core.c cros
	gcc -o cros-core.o cros-core.c build/cros.a

sample-publisher: sample-publisher.c cros
	gcc -o sample-publisher.o sample-publisher.c build/cros.a

cros: master messages publisher node
	ar rcs build/cros.a build/master.o build/messages.o build/node.o build/publisher.o 

master: cross/master/master.c
	gcc -o build/master.o -c cross/master/master.c -pthread

messages: cross/messages/print.c
	gcc -o build/messages.o -c cross/messages/print.c

node: cross/node/node.c
	gcc -o build/node.o -c cross/node/node.c 

publisher: cross/publisher/publisher.c
	gcc -o build/publisher.o -c cross/publisher/publisher.c