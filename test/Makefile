creadable_test: test.o creadable.o
	@gcc -o creadable_test test.o creadable.o

test.o: test.c
	@gcc test.c -o test.o -c

creadable.o: ../src/creadable.c
	@gcc ../src/creadable.c -o creadable.o -c

clean:
	@rm *.o
