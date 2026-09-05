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

void	take_dongle(t_dev *coders, long long time)
{
	t_dev	*next_dev;
	t_dev	*prev_dev;

	next_dev = &coders->all_coders[coders->next_dev];
	prev_dev = &coders->all_coders[coders->prev_dev];
	printf("%llu %d has taken a dongle\n", time, coders->nb);
	printf("%llu %d has taken a dongle\n", time, coders->nb);
	if (coders->state == 0)
	{
		next_dev->dongle.is_used = true;
		prev_dev->dongle.is_used = true;
	}
}

int	is_dongle_free(t_dev *dev)
{
	t_dev	*next;
	t_dev	*prev;

	next = &dev->all_coders[dev->next_dev];
	prev = &dev->all_coders[dev->prev_dev];
	if (next->dongle.is_used == false && prev->dongle.is_used == false)
		return (1);
	return (0);
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
