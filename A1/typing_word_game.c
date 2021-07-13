/*
 *	Theo Rowlett
 *	CS201-Spring 2021
 *	Project A1: Create a program that it takes a user to match a randomized input
 *		of the phrase "The quick brown fox jumps over the lazy dog."
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#define ARRAY_SIZE 9
#define MAX_STRING 10

char ** build_array();
void display_pangram(char ** pangram);
int play_game(char ** pangram);
void free_mem(char ** pangram);

int main() {

	struct timeval tv;
	gettimeofday(&tv,NULL);
	srand(tv.tv_sec);
	char ** pangram = build_array();
	display_pangram(pangram);
	printf("This is a game that tests typing speed\n");
	printf("Type the following words:\n");

	play_game(pangram);

	free_mem(pangram);
	exit(0);
}

char ** build_array() {
	int i = 0;
	char ** pangram = malloc(sizeof(char*)*ARRAY_SIZE);
	for (i; i < ARRAY_SIZE; i++)
		pangram[i] = malloc(MAX_STRING+1);

	strncpy(pangram[0],"The",MAX_STRING);
	strncpy(pangram[1],"quick",MAX_STRING);
	strncpy(pangram[2],"brown",MAX_STRING);
	strncpy(pangram[3],"fox",MAX_STRING);
	strncpy(pangram[4],"jumps",MAX_STRING);
	strncpy(pangram[5],"over",MAX_STRING);
	strncpy(pangram[6],"the",MAX_STRING);
	strncpy(pangram[7],"lazy",MAX_STRING);
	strncpy(pangram[8],"dog",MAX_STRING);
	return pangram;
}



int play_game(char ** pangram) {
	struct timeval begin, end, result;
	bool flag;
	char word[MAX_STRING];
	int j[ARRAY_SIZE];
	int i = 0;
	int rand_val;
	gettimeofday(&begin,NULL);
	while (i < ARRAY_SIZE) {
		rand_val = rand() % ARRAY_SIZE;
		if (j[rand_val]!=1) {
			flag = false;
			while (flag == false) {
				printf("Word #%i is %s: ",i+1,pangram[rand_val]);
				scanf("%10s",word);
				while ((getchar()) != '\n');
				if (strncmp(word,pangram[rand_val],MAX_STRING)==0)
					flag = true;
				else
					flag = false;
			}
			++i;
			j[rand_val] = 1;
		}
	}
	gettimeofday(&end,NULL);
	timersub(&end,&begin,&result);
	printf("Elapsed time: %ld.%6ld seconds \n",result.tv_sec,result.tv_usec);
	return 1;
}

void display_pangram(char ** pangram) {
	int i;
	for (i = 0; i<ARRAY_SIZE; ++i)
	{
		printf("%s ",pangram[i]);
	}
	printf("\n");
	return;
}

void free_mem(char ** pangram) {
	int i = 0;
	for (i; i < ARRAY_SIZE; i++) {
		free(pangram[i]);
	}
	free(pangram);
}
