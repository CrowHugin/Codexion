/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 10:09:12 by bastien           #+#    #+#             */
/*   Updated: 2026/08/30 10:22:49 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <stdio.h>

void	take_dongle(t_dev *coders)
{
	t_dev	*next_dev;
	t_dev	*prev_dev;

	next_dev = &coders->all_coders[coders->next_dev];
	prev_dev = &coders->all_coders[coders->prev_dev];
	printf("nb dev: %d\n", coders->nb);
	printf("dev has dongle: %d\n", coders->dongle.is_used);
	printf("next_dev: %d\n\n", next_dev->nb);
	if (coders->state == 0)
	{
		next_dev->dongle.is_used = true;
		prev_dev->dongle.is_used = true;
	}
	printf("next_dev has dongles: %d\n", next_dev->dongle.is_used);
	printf("prev_dev has dongles: %d\n", prev_dev->dongle.is_used);
}

int	is_dongle_free(t_dev *dev)
{
	t_dev	*next;
	t_dev	*prev;

	next = &dev->all_coders[dev->next_dev];
	prev = &dev->all_coders[dev->prev_dev];
	if (next->dongle.is_used == false && prev->dongle.is_used == false)
		return (0);
	return (1);
}

void	free_dongle(t_dev *dev)
{
	t_dev	*next;
	t_dev	*prev;

	next = &dev->all_coders[dev->next_dev];
	prev = &dev->all_coders[dev->prev_dev];
	next->dongle.is_used = false;
	prev->dongle.is_used = false;
}
