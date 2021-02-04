#include <stdio.h>
#include <string.h>

void playPtr(char *c)
{
    ++c;
    printf("In playPtr: *c points to: %c\n", *c);
}

int main(void)
{
    char *c = "hello";
    char *q = "mello";
    strcpy(c, q);

    printf("In main: *c points to: %c\n", *c);
    playPtr(c);
    printf("In main: *c points to: %c\n", *c);
    return 0;
}
