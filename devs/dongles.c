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
#include "../queue/queue.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	take_dongle(t_dev *coders, long long time)
{
	t_dev	*next_dev;
	t_dev	*prev_dev;

	next_dev = &coders->all_coders[coders->next_dev];
	prev_dev = &coders->all_coders[coders->prev_dev];
	next_dev->dongle.is_used = true;
	prev_dev->dongle.is_used = true;
	printf("%llu %d has taken a dongle\n", time, coders->nb);
	printf("%llu %d has taken a dongle\n", time, coders->nb);
}

void	acquire_dongle(t_dev *dev, t_dongle *d,
		int coder_id, long long deadline,
		int sched, long long start_time)
{
	pthread_mutex_lock(&d->mutex);
	while (d->is_used
		|| get_time() < d->available_at
		|| !is_top(d, coder_id, sched))
	{
		if (!in_queue(d, coder_id))
			enqueue(d, coder_id, deadline);
		pthread_mutex_unlock(&d->mutex);
		check_burnout(dev, start_time);
		if (atomic_load(dev->keep_running) == 0)
			return ;
		usleep(50);
		pthread_mutex_lock(&d->mutex);
	}
	d->is_used = true;
	dequeue(d, coder_id);
	pthread_mutex_unlock(&d->mutex);
}

void	release_dongle(t_dongle *d, int cooldown)
{
	pthread_mutex_lock(&d->mutex);
	d->is_used = false;
	d->available_at = get_time() + cooldown;
	pthread_mutex_unlock(&d->mutex);
}
