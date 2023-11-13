final: cros-core samples

samples: sample-publisher sample-subscriber sample4

sample1: cros sample1/publisher.c
	gcc -o sample1/publisher.o sample1/publisher.c

sample4: cros sample4/nodeA.c sample4/nodeB.c
	gcc -o sample4/nodeA.o sample4/nodeA.c build/cros.a
	gcc -o sample4/nodeB.o sample4/nodeB.c build/cros.a

cros-core: cros-core.c cros
	gcc -o cros-core.o cros-core.c build/cros.a

sample-publisher: sample-publisher.c cros
	gcc -o sample-publisher.o sample-publisher.c build/cros.a 

sample-subscriber: sample-subscriber.c cros
	gcc -o sample-subscriber.o sample-subscriber.c build/cros.a

cros: linkedlist networking messages master node subscriber publisher 
	ar rcs build/cros.a build/master.o build/messages.o build/node.o \
	build/publisher.o build/subscriber.o build/linkedlist.o build/networking.o 

master: cross/master/master.c
	gcc -o build/master.o -c cross/master/master.c -pthread

messages: cross/messages/print.c
	gcc -o build/messages.o -c cross/messages/print.c

node: cross/node/node.c
	gcc -o build/node.o -c cross/node/node.c -pthread

publisher: cross/publisher/publisher.c
	gcc -o build/publisher.o -c cross/publisher/publisher.c

subscriber: cross/subscriber/subscriber.c
	gcc -o build/subscriber.o -c cross/subscriber/subscriber.c

linkedlist: cross/linkedlist/linkedlist.c
	gcc -o build/linkedlist.o -c cross/linkedlist/linkedlist.c

networking: cross/networking/networking.c
	gcc -o build/networking.o -c cross/networking/networking.c
