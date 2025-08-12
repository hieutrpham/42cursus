#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_bit(unsigned char octet)
{
	unsigned char bit = 0;
	int i = 8;

	while (i--)
	{
		bit = ((octet >> i) & 1) + '0';
		write(1, &bit, 1);
	}
}

unsigned char reverse_bits(unsigned char octet)
{
	int i = 8;
	unsigned char res = 0;

	while (i--)
	{
		res = (res << 1) | (octet & 1);
		octet = octet >> 1;
	}
	return res;
}

unsigned char swap_bit(unsigned char oc)
{
    return (oc >> 4 | oc << 4);
}

int main(int ac, char **av)
{
	unsigned char bit = atoi(av[1]);
	print_bit(bit);
	printf("\n");
	unsigned char r_bit = reverse_bits(bit);
	print_bit(r_bit);
    unsigned char sw_bit = swap_bit(bit);
	printf("\n");
    print_bit(sw_bit);
}
