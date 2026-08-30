/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:23:45 by bastien           #+#    #+#             */
/*   Updated: 2026/08/30 00:29:29 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <stdio.h>

void	set_up_dev(t_dev *coders, int len, int *queue)
{
	int		i;

	i = 0;
	while (i < len)
	{
		coders[i].nb = i + 1;
		coders[i].has_doggle = 1;
		coders[i].state = STATE_DEBUG;
		coders[i].all_coders = coders;
		coders[i].queue = queue;
		coders[i].next_dev = (i + 1) % len;
		coders[i].next_dev = (i + len - 1) % len;
		i++;
	}
}

void	change_state(t_dev *dev)
{
	if (dev->state == 0)
	{
		dev->state = 1;
		printf("X %d is compiling\n", dev->nb);
	}
	else if (dev->state == 1)
	{
		dev->state = 2;
		printf("X %d is debugging\n", dev->nb);
	}
	else if (dev->state == 2)
	{
		dev->state = 0;
		printf("X %d is refactoring\n", dev->nb);
	}
}

void	*dev_behaivor(void *arg)
{
	t_dev *coders = (t_dev *)arg;
	take_dongle(coders);

	return (NULL);
}
