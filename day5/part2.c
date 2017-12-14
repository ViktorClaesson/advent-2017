#include <stdio.h>
#include <stdlib.h>

struct point {
  int value;
  struct point *next;
  struct point *prev;
};

int main(int argc, char *argv[]) {
  FILE *fp;
  if((fp = fopen("./input", "r")) == NULL) {
    perror("error opening file");
    return 1;
  }

  // INIT
  size_t size = 0;
  char *line = NULL;
  struct point start = {0, NULL, NULL};
  if(getline(&line, &size, fp) != -1) {
    start.value = atoi(line);
  }

  struct point *curr = &start;
  struct point *next;
  while(getline(&line, &size, fp) != -1) {
    next = malloc(sizeof(struct point));
    next->value = atoi(line);
    next->prev = curr;
    curr->next = next;
    curr = next;
  }
  free(line);

  // SOLVE PUZZLE
  struct point *position = &start;
  int moves = 0;
  while(position != NULL) {
    moves += 1;
    int steps = position->value;
    if(position->value >= 3) {
      position->value-=1;
    } else {
      position->value+=1;
    }
    while(steps > 0) {
      if(position == NULL) break;
      position = (position->next);
      steps -= 1;
    }
    while(steps < 0) {
      if(position == NULL) break;
      position = (position->prev);
      steps += 1;
    }
  }

  printf("It took %d moves\n", moves);

  if(fclose(fp)) {
    perror("error closing file");
    return 1;
  }
}
