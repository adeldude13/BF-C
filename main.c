#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"


char *readConsole() {
	int len = 4;
	char *str = malloc(sizeof(char) * len);
	int index = 0;
	int c;
	while((c = fgetc(stdin)) != EOF && c != '\n') {
		str[index++] = c;
		if(len == index) {
			len = len * 2;
			str = realloc(str, sizeof(char)*(len));
		}
	}
	str[index] = '\0';
	return str;
}



void console() {
	while(1) {
		printf("BF>> ");
		char *data = readConsole();
		if(!strcmp(data, "exit")) exit(0);
		interpret(data);	
		free(data);
	}
}

char *readFile(FILE *fp) {
	int len = 4;
	char *str = malloc(sizeof(char) * len);
	int index = 0;
	int c;
	while((c = fgetc(fp)) != EOF) {
		str[index++] = c;
		if(len == index) {
			len = len * 2;
			str = realloc(str, sizeof(char)*(len));
		}
	}
	str[index] = '\0';
	return str;	
}



void runFile(char *file) {
	FILE *fp = fopen(file, "r");
	char *data = readFile(fp);			
	fclose(fp);
	interpret(data);
	free(data);
}

int main(int argc, char *argv[]) {
	
	if(argc == 1) {
		console();
	} else if(argc == 2) {
		runFile(argv[1]);
	} else {
		printf("Usage: bf [file.bf]");	
	}

	return 0;
}
