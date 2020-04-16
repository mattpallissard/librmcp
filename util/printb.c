#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void printb(uint64_t i)
{
        char p[65];
        uint8_t j = sizeof(p) - 1;
        p[j] = '\0';
        while (j) {
                p[--j] = (i & 0x1) ? '1' : '0';
                i >>= 1;
        }
        printf("%s\n", p);
}


int main(int argc, char *argv[])
{
	int i = 1;
	while(i < argc)
		printb(strtoul(argv[i++], NULL, 10));
}
