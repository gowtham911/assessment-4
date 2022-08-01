#include <stdio.h>
#include <stdlib.h>

typedef struct Total {
  int lines;
  int words;
  int bytes;
} Total;

Total *new_Total(int lines, int words, int bytes) {
  Total *t = (Total *)malloc(sizeof(Total));
  t->lines = lines;
  t->words = words;
  t->bytes = bytes;
  return t;
}

void updateTotal(Total *t, int lines, int words, int bytes) {
  t->lines += lines;
  t->words += words;
  t->bytes += bytes;
}

void readStdin(Total *t, char c) {
  int lines = 0, words = 0, bytes = 0, startWord = 0;
  char ch;
  while ((ch = fgetc(stdin)) != EOF) {
    bytes++;
    if (ch == '\n') {
      lines++;
    }
    if (ch != ' ' && ch != '\n' && ch != '\r' && ch != '\t') {
      startWord = 1;
    }
    if ((ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') &&
        startWord == 1) {
      words++;
      startWord = 0;
    }
  }
  updateTotal(t, lines, words, bytes);
  if (c == '\0') {
    printf(" %d %d %d\n", lines, words, bytes);
  } else {
    printf(" %d %d %d %c\n", lines, words, bytes, c);
  }
}

void readFile(Total *t, char *filename, FILE *fp) {
  int lines = 0, words = 0, bytes = 0, startWord = 0;
  char ch;
  if (fp == NULL) {
    printf("%s: No such file or directory\n", filename);
    exit(1);
  }
  while ((ch = fgetc(fp)) != EOF) {
    bytes++;
    if (ch == '\n') {
      lines++;
    }
    if (ch != ' ' && ch != '\n' && ch != '\r' && ch != '\t') {
      startWord = 1;
    }
    if ((ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') &&
        startWord == 1) {
      words++;
      startWord = 0;
    }
  }
  updateTotal(t, lines, words, bytes);
  printf(" %d %d %d %s\n", lines, words, bytes, filename);
}

void readArgs(Total *t, int argc, char *argv[]) {
  FILE *fp;
  for (int i = 1; i < argc; i++) {
    if (*argv[i] == '-') {
      readStdin(t, '-');
      clearerr(stdin);
    } else {
      fp = fopen(argv[i], "r");
      readFile(t, argv[i], fp);
      fclose(fp);
    }
  }
  if (argc > 2) {
    printf(" %d %d %d total\n", t->lines, t->words, t->bytes);
  } else {
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  Total *t = new_Total(0, 0, 0);
  if (argc < 2) {
    readStdin(t, '\0');
    return 0;
  }
  readArgs(t, argc, argv);
  free(t);
  return 0;
}
