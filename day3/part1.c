#include <stdio.h>
#include <stdlib.h>

struct bound {
  int level;
  int low;
  int high;
} b;

int sq(int a) {
  return a * a;
}

int min_2(int a, int b) {
  if(a < b) return a;
  else return b;
}

int min_4(int a, int b, int c, int d) {
  return min_2(min_2(a, b), min_2(c, d));
}

void findBounds(int n) {
  int i = 1;
  int level = 1;
  while(sq(i+2) < n) {
    i += 2;
    level++;
  }
  b.low = i*i + 1;
  b.high = (i+2)*(i+2);
  b.level = level;
}

int main(int argc, char * argv[]) {
  if(argc < 2) {
    perror("Argc < 2");
    return 1;
  }

  int n = atoi(*(argv+1));

  if(n < 1) {
    perror("n < 1");
    return 1;
  }

  if(n == 1) {
    printf("Data from square 1 is carried 0 steps\n");
  } else {
    findBounds(n);
    int side = 1 + b.level * 2;
    int middle1 = (b.high + (b.high - side + 1)) / 2;
    int middle2 = middle1 - (side - 1);
    int middle3 = middle2 - (side - 1);
    int middle4 = middle3 - (side - 1);

    //printf("middle: %d %d %d %d\n", middle1, middle2, middle3, middle4);
    int min_to_middle = min_4(abs(n - middle1), abs(n - middle2), abs(n - middle3), abs(n - middle4));
    int road = b.level + min_to_middle;

    //printf("%d to %d @ level: %d\n", b.low, b.high, b.level);
    //printf("min_to_middle: %d\n", min_to_middle);
    //printf("road: %d\n", road);
    printf("Data from square 1 is carried %d steps\n", road);
  }
}
