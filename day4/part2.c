#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str) {
  int length = strlen(str);
  for(int i = 0; i < length - 1; i++) {
    int k = i;
    for(int j = i+1; j < length; j++) {
      if(str[j] < str[k]) {
        k = j;
      }
    }
    char temp = str[k];
    str[k] = str[i];
    str[i] = temp;
  }
}

int process_line(char *line) {
  char *line_copy = line;

  int spaces = 0;
  int len = strlen(line_copy);
  for(int i = 0; i < len; i++) {
    if(line_copy[i] == ' ')
      spaces += 1;
  }

  char *words[spaces+1];
  char *current_word;

  int len2 = sizeof(words) / sizeof(*words);

  for(int i = 0; i < len2; i++) {
    words[i] = strsep(&line_copy, " \n");
    sort_string(words[i]);
  }

  for(int i = 0; i < len2; i++) {
    for(int j = i+1; j < len2; j++) {
      if(strcmp(words[i], words[j]) == 0) {
          return 0;
      }
    }
  }

  return 1;
}

int main(int argc, char * argv[]) {
  FILE *fp;
  if((fp = fopen("./input", "r")) == NULL) {
    perror("error reading file");
    return 1;
  }

  size_t size = sizeof(char);
  char *line = malloc(size);
  int valid = 0;
  while(getline(&line, &size, fp) != -1) {
    valid += process_line(line);
  }

  if(line) {
    free(line);
    line = NULL;
  }

  printf("There are %d valid lines\n", valid);

  if(fclose(fp)) {
    perror("error closing file");
    return 1;
  }
  
  return 0;
}
