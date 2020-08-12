all: main
main:
	gcc -o main main.c -lm
clean:
	rm -f main
	rm -f LinkedList.h.gch
	rm -f Node.h.gch 
