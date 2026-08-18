#include <stdio.h>
#include "dev.h"

void	print_base_infos(t_dev coders, int j)
{
	char *var;
	printf("Coder %d:\n", j + 1);
	printf("	numbers: %d\n", coders.nb);
	printf("	has_doggle: %d\n", coders.has_doggle);
	if (coders.state == 0)
		var = "compile";
	else if (coders.state == 1)
		var = "debug";
	else
		var = "refactor";
	printf("	state: %s\n", var);
}

void	print_devs_infos(t_dev *coders, int len)
{
	int	j;

	j = 0;
	printf("nb coders: %d\n", len);
	print_base_infos(coders[j], j);
	printf("	has_doggle right: %d\n", coders[j + 1].has_doggle);
	printf("	has_doggle left: %d\n", coders[len - 1].has_doggle);
	j++;
	while (j < len - 1)
	{
		print_base_infos(coders[j], j);
		printf("	has_doggle right: %d\n", coders[j + 1].has_doggle);
		printf("	has_doggle left: %d\n", coders[j - 1].has_doggle);
		j++;
	}
	print_base_infos(coders[j], j);
	printf("	has_doggle right: %d\n", coders[0].has_doggle);
	printf("	has_doggle left: %d\n", coders[j].has_doggle);
}
