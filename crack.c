#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

/*
 * crack.c is able to encode and decode binary encoded messages using
 * ascii representation.
 */

/* This routine accepts a binary string and returns it as a character */
char
binary_to_character(char *input) {
	int ii;
	char output = 0;
	for (ii = 0; ii < 8; ii++) {
		if (input[ii] == '1') {
			output += (1 << (7 - ii));
		}
	}
	return output;
}

/* Accepts a character and returns the binary encoding in the out arg. */
void
character_to_binary(char in, char *out, int len)
{
	int ii;
	assert(len >= 8);
	for (ii = 0; ii < 8; ii++) {
		if ((1 << 7) & in) {
			out[ii] = '1';
		} else {
			out[ii] = '0';
		}
		in = in << 1;
	}
}

FILE*
open_file(char *file) {
	FILE *fptr;
	if (strcmp(file, "-") == 0) {
		fptr = stdin;
	} else {
		fptr = fopen(file, "r");
	}
	if (fptr == NULL) {
		printf("Cannot open %s\n", file);
		exit(2);
	}
	return fptr;
}

/*
 * Here we accept a filename,open the file and call binary_to_character
 * on each binary letter in the file.
 */

void
decode(char *file) {
	char buf[1024];
	char *token;
	FILE *fptr = open_file(file);
	while (fgets(buf,sizeof(buf), fptr)) {
		token = (char*)strtok(buf, " ");
		if (token == NULL) {
			printf("No tokens\n");
			break;
		}
		do {
			printf("%c", binary_to_character(token));
			token = (char *)strtok(NULL, " ");
		} while(token);
	}
	printf("\n");
	fclose(fptr);
}

/*
 * Here we accept a filename, open the file and call character_to_binary
 * on each ascii letter in the file.
 */

void
encode(char *file) {
	char buf[1024];
	int binary_count = 0;
	FILE *fptr = open_file(file);
	while (fgets(buf, sizeof(buf), fptr)) {
		int len = strnlen(buf, 1024);
		int ii;
		for (ii = 0; ii < len; ii++) {
			char binbuf[8];
			character_to_binary(buf[ii], binbuf, 8);
			printf("%s ", binbuf);
			binary_count++;
			/* No more than 8 on a line */
			if (binary_count == 8) {
				printf("\n");
				binary_count = 0;
			}
		}
	}
	fclose(fptr);
	printf("\n");
}

int
main(int argc, char **argv) {
	int opt;
	while((opt = getopt(argc, argv, "d:e:")) != -1) {
		switch(opt) {
		case 'd':
			decode(optarg);
		break;
		case 'e':
			encode(optarg);
		break;
		default:
			printf("-d <file> | -e <file>\n");
			break;
		}
	}
	return 0;
}
