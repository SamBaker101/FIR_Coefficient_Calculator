all: src/main.c
	gcc src/main.c -o calc

clean: 
	$(RM) calc
