/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:23:45 by bastien           #+#    #+#             */
/*   Updated: 2026/08/17 22:53:24 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <stdlib.h>
#include <stdio.h>

int	set_up_dev(int *options)
{
	int		i;
	int		j;
	t_dev	*coders;

	j = 0;
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
	printf("nb coders: %d\n", options[0]);
	while (j < options[0])
	{
		printf("Coder %d:\n", j + 1);
		printf("	numbers: %d\n", coders[j].nb);
		printf("	has_doggle: %d\n", coders[j].has_doggle);
		j++;
	}
	free(coders);
	return (0);
}
