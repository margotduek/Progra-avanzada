#Simple example of a makefile

word: word.c
	gcc word.c -o word - Wall

# Clear the compiled files
clean:
	rm -rf *.o word

#indicate the rules that do not refer to a file
.PHONY: clean
