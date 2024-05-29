all:
	gcc ./*.c -DLOCKFREE -pthread -O2 -o queue_lockfree --std=c99
	gcc ./*.c -DMUTEX -pthread -O2 -o queue_mutex --std=c99
	chmod u+x ./run_queue.sh
	./run_queue.sh

clean:
	rm -f ./queue_lockfree
	rm -f ./queue_mutex
