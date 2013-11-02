#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mm_malloc.h>
#include <search.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

#define Dictionary "./big.txt"
#define DicSize	3000000

const char delim[]    = ".,:;`/\"+-_(){}[]<>*&^%$#@!?~/|\\=1234567890 \t\n";
const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

char *strtolower(char *word) {
	char *s;
	for (s = word; *s; s++) {
		*s = tolower(*s);
	}
	return word;
}

ENTRY *find(char *word) {
	ENTRY e;
	e.key = word;
	return hsearch(e, FIND);
}

int update(char *word) {
	ENTRY *e = find(word);
	if (!e)
		return 0;
	e->data++;
	return 1;
}

int read_file(ENTRY dict) {
	char *file, *word, *w;
	FILE *fp = fopen(Dictionary, "r");
	struct stat f;

	if (!fp) {
		return 0;
	}

	if (stat(Dictionary, &f))
		return 0;

	file = (char*)malloc(f.st_size);
	if (!file) {
		fclose(fp);
		return 0;
	}

	fread(file, sizeof(char), f.st_size, fp);
	word = strtok(file, delim);
	while (word != NULL) {
		w = strtolower(strdup(word));
		if (!update(w)) {
			dict.key = w;
			dict.data = 0;
			hsearch(dict, ENTER);
		}
		word = strtok(NULL, delim);
	}
	free(file);
	fclose(fp);
	return 1;
}

int edits1_rows(char *word) {
	register int size = strlen(word);

}

char *correct(char *word) {
	char **e1, **e2, *e1_word, *e2_word, *res_word = word;
	int e1_rows, e2_rows;
	if (find(word)) {
		return word;
	}
	e1_rows = edits1_rows(word);
}

int main(int argc, char **argv)
{
	char *correct_word;
	ENTRY dict;

	hcreate(DicSize);

	if (!read_file(dict)) {
		return -1;
	}

	correct_word = correct(argv[1]);
}
