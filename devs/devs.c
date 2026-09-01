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
#include "../queue/queue.h"
#include <stdio.h>
#include <unistd.h>

void	set_up_dev(t_dev *coders, int *options, int *queue)
{
	int		i;

	i = 0;
	while (i < options[0])
	{
		coders[i].nb = i + 1;
		coders[i].state = STATE_DEBUG;
		coders[i].all_coders = coders;
		coders[i].queue = queue;
		coders[i].next_dev = (i + 1) % options[1];
		coders[i].prev_dev = (i + options[1] - 1) % options[1];
		coders[i].options = options;
		coders[i].dongle.nb = i + 1;
		coders[i].dongle.is_used = false;
		coders[i].dongle.cooldown = options[6];
		i++;
	}
}

void	change_state(t_dev *dev, int *size)
{
	(void) size;
	if (dev->state == 0)
	{
		dev->state = 1;
		if (is_dongle_free(dev))
		{
			printf("X %d is compiling\n", dev->nb);
			usleep(dev->options[2]);
		}
		else
			add_queue(&dev->queue, size, dev->nb);
	}
	else if (dev->state == 1)
	{
		dev->state = 2;
		printf("X %d is debugging\n", dev->nb);
		usleep(dev->options[3]);
	}
	else if (dev->state == 2)
	{
		dev->state = 0;
		printf("X %d is refactoring\n", dev->nb);
		usleep(dev->options[4]);
	}
}

void	*dev_behaivor(void *arg)
{
	t_dev	*coders;
	int		queue_size;
	int		i;

	coders = (t_dev *)arg;
	i = 0;
	queue_size = 0;
	while (i < 10)
	{
		change_state(coders, &queue_size);
		i++;
	}
	return (NULL);
}
