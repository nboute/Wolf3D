#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void	printbox(int val)
{
	if (!val)
		printf("\x1b[35m%C", 0x2588);
	else if (val == 1)
		printf("\x1b[35m%C", 0x2579);
	else if (val == 2)
		printf("\x1b[35m%C", 0x2578);
	else if (val == 3)
		printf("\x1b[35m%C", 0x251B);
	else if (val == 4)
		printf("\x1b[35m%C", 0x257A);
	else if (val == 5)
		printf("\x1b[35m%C", 0x2517);
	else if (val == 6)
		printf("\x1b[35m%C", 0x2503);
	else if (val == 7)
		printf("\x1b[35m%C", 0x253B);
	else if (val == 8)
		printf("\x1b[35m%C", 0x257B);
	else if (val == 9)
		printf("\x1b[35m%C", 0x2501);
	else if (val == 10)
		printf("\x1b[35m%C", 0x2513);
	else if (val == 11)
		printf("\x1b[35m%C", 0x252B);
	else if (val == 12)
		printf("\x1b[35m%C", 0x250F);
	else if (val ==13)
		printf("\x1b[35m%C", 0x2523);
	else if (val == 14)
		printf("\x1b[35m%C", 0x2533);
	else if (val == 15)
		printf("\x1b[35m%C", 0x254B);

}

int		main(void)
{
	setlocale(LC_ALL, "");
	int	i = 0;
	while (i < 16)
	{
		printbox(i);
		printf("\n-Y:%d|-X:%d|X:%d|Y:%d\n", i % 2, (i % 4) / 2, (i % 8) / 4, i / 8);
		i++;
	}
}
