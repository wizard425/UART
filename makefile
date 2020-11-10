Schicht: schicht2.o schicht1.o
	gcc -o Schicht schicht2.o schicht1.o

schicht2.o: schicht2.c schicht1.h
	gcc -c schicht2.c

schicht1.o: schicht1.c schicht1.h
	gcc -c schicht1.c
