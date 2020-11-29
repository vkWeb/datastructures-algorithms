#include <stdio.h>

int euclidGcd(int a, int b)
{
  while (b != 0)
  {
    int remainder = a % b;
    a = b;
    b = remainder;
  }
  return a;
}

int main(void)
{
  printf("%d\n", euclidGcd(100, 300));
  return 0;
}
