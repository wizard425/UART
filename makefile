testprogram: program.o schicht2.o schicht1.o
	gcc -o testprogram program.o schicht2.o schicht1.o

program.o: program.c schicht2.h
	gcc -c program.c

schicht2.o: schicht2.c schicht1.h
	gcc -c schicht2.c

schicht1.o: schicht1.c schicht1.h
	gcc -c schicht1.c
