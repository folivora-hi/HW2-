all:main.o

main.o:main.c
	gcc main.c -o main
	./main -d 1e6 -q 1e4 -arr -bs -bst -ll
	./main -d 1e6 -q 1e5 -arr -bs -bst -ll
	

