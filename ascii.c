#include <stdio.h>

int main()
{
    unsigned char i;
    for(i=0; i<128; i++)
        printf("%d = %c\n", i, i);

    return 0;
}
