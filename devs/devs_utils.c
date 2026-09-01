/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:34:21 by bastien           #+#    #+#             */
/*   Updated: 2026/08/30 00:34:36 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "dev.h"

void	print_base_infos(t_dev coders, int j)
{
	char	*var;

	printf("Coder %d:\n", j + 1);
	printf("	numbers: %d\n", coders.nb);
	printf("	has_doggle: %d\n", coders.dongle.is_used);
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
	printf("	has_doggle right: %d\n", coders[j + 1].dongle.is_used);
	printf("	has_doggle left: %d\n", coders[len - 1].dongle.is_used);
	j++;
	while (j < len - 1)
	{
		print_base_infos(coders[j], j);
		printf("	has_doggle right: %d\n", coders[j + 1].dongle.is_used);
		printf("	has_doggle left: %d\n", coders[j - 1].dongle.is_used);
		j++;
	}
	print_base_infos(coders[j], j);
	printf("	has_doggle right: %d\n", coders[0].dongle.is_used);
	printf("	has_doggle left: %d\n", coders[j].dongle.is_used);
}
