prologIC : main.o analysers.o compiler.o fcall.o interpreter.o
	gcc -g3 -o prologIC main.o analysers.o compiler.o fcall.o interpreter.o


main.o : main.c analysers.h errors.h compiler.h fcall.h
	gcc -g3 -c main.c
	
analysers.o : analysers.c errors.h analysers.h
	gcc -g3 -c analysers.c
	
compiler.o : compiler.c compiler.h heap.h errors.h
	gcc -g3 -c compiler.c
	
fcall.o : fcall.c errors.h	 fcall.h interpreter.h
	gcc -g3 -c fcall.c	
	
interpreter.o: interpreter.c interpreter.h 
	gcc -g3 -c interpreter.c	
