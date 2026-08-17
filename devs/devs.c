/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:23:45 by bastien           #+#    #+#             */
/*   Updated: 2026/08/17 23:39:39 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <stdlib.h>
#include <stdio.h>

void	print_base_infos(t_dev coders, int j)
{
	printf("Coder %d:\n", j + 1);
	printf("	numbers: %d\n", coders.nb);
	printf("	has_doggle: %d\n", coders.has_doggle);
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

int	set_up_dev(int *options)
{
	int		i;
	t_dev	*coders;

	i = 0;
	coders = malloc(sizeof(t_dev) * options[0]);
	if (!coders)
		return (1);
	while (i < options[0])
	{
		coders[i].nb = i + 1;
		coders[i].has_doggle = 1;
		i++;
	}
	coders[2].has_doggle = 0;
	coders[0].has_doggle = 0;
	print_devs_infos(coders, options[0]);
	free(coders);
	return (0);
}
