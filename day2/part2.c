#include <stdio.h>
#include <string.h>

void read_input(FILE *fp, int input[16][16]) {
  char x;
  int curr_num = 0;
  int col_pointer = 0;
  int row_pointer = 0;
  while((x = fgetc(fp)) != EOF) {
    if(x == '\t') {
      input[row_pointer][col_pointer] = curr_num;
      col_pointer += 1;
      curr_num = 0;
    } else if(x == '\n') {
      input[row_pointer][col_pointer] = curr_num;
      col_pointer = 0;
      row_pointer += 1;
      curr_num = 0;
    } else {
      curr_num *= 10;
      curr_num += (x - '0');
    }
  }
}

int row_checksum(int input[16][16], int row) {
  for(int curr_col = 0; curr_col < 15; curr_col++) {
    for(int next_col = curr_col+1; next_col < 16; next_col++) {
      int curr = input[row][curr_col];
      int next = input[row][next_col];
      if((curr % next) == 0) {
        return curr / next;
      } else if((next % curr) == 0) {
        return next / curr;
      }
    }
  }
  return -1;
}

int main() {
  FILE *fp;
  printf("%s\n", "Opening file");
  if((fp = fopen("./input", "r")) == NULL) {
    perror("Ops.");
    return 1;
  }

  int input[16][16];
  read_input(fp, input);

  int sum = 0;
  for(int row = 0; row < 16; row++) {
    int row_sum = row_checksum(input, row);
    sum += row_sum;
    printf("row sum: %d\n", row_sum);
  }
  printf("tot sum: %d\n", sum);

  printf("%s\n", "Closing file");
  if(fclose(fp)) {
    perror("Ops.");
    return 1;
  }
  return 0;
}
