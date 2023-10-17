final: cros-core.c master messages sample-publisher
	gcc -o cros-core.o cros-core.c build/master.o build/messages.o -pthread

sample-publisher: sample-publisher.c node
	gcc -o sample-publisher.o sample-publisher.c build/node.o

master: cross/master/master.c
	gcc -o build/master.o -c cross/master/master.c -pthread

messages: cross/messages/print.c
	gcc -o build/messages.o -c cross/messages/print.c

node: cross/node/node.c
	gcc -o build/node.o -c cross/node/node.c