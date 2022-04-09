#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX 10000


unsigned char arr[MAX];
int current = 0;



typedef struct {
	char *code;	
	int curr;
	int line;
} Interp;


Interp source;


int isAtEnd() {
	return source.code[source.curr] == '\0';
}


char advance() {
	if(isAtEnd()) return '\0';
	return source.code[source.curr++];
}

char back() {
	return source.code[source.curr--];
}


char prev() {
	if(source.curr == 0) return '\0';
	return source.code[source.curr-1];
}


char currentVal() {	
	return source.code[source.curr];
}

int isCommand(char c) {
	switch(c) {
		case '\n':
		case '>':
		case '<':
		case '+':
		case '-':
		case '.':
		case ',':
		case ']':
		case '[':
			return 1;
	}
	return 0;
}


void skip() {
	while(!isAtEnd() && !isCommand(currentVal())) {
			advance();
	}
}


void error(char *m) {
	fprintf(stderr, "Error at %c line %i", prev(), source.line);
	printf(" : %s", m);
	exit(0);
}


void inc() {
	if(current >= MAX) {
			error("Cant Increment any More!");	
	}
	current++;	
}


void dec() {
	if(current <= 0) {
		error("Cant Decrement Any More!");
	}
	current--;
}

void add() {	
	if(arr[current] >= 255) {arr[current] = (unsigned char)0; return;}
	arr[current]++;
}

void sub() {
	if(arr[current] == (char)0) arr[current] = (char)255;
	arr[current]--;
}

void goBack() {
	while(source.code[source.curr] != '[') {
		source.curr--;	
	}
}


void input() {
	char c = fgetc(stdin);
	arr[current] = c;
}


void outp() {
	printf("\n%i\n", arr[current]);
}

void skipToEnd() {
	while(!isAtEnd() && currentVal() != ']') {
		advance();
	}
	if(isAtEnd()) error("No Ending For The Loop!");
}



void walkSource() {
	int loopStart;	
	int inLoop = 0;
	skip();
	char c;
	while((c=advance()) != '\0') {
		switch(c) {
			case '\n':
				source.line++;
				break;
			case '>':
				inc();
				break;
			case '<':
				dec();
				break;
			case '+':
				add();
				break;
			case '-':
				sub();
				break;
			case ',':
				input();
				break;
			case '.':
				outp();
				break;
			case '[': {
				if(arr[current] == 0) {
					inLoop = 0;
					skipToEnd();
					break;
				}
					loopStart = source.curr;
					inLoop = 1;
					continue;
			}
			case ']': {
				if(inLoop) {goBack(); break;}
				else {break;}
			}

		}
		skip();
	}
}


void interpret(char *src) {
	source.code = src;		
	source.curr = 0;
	source.line = 1;
	walkSource();
}
