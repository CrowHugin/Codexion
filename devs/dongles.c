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
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void lock_two_dongles(t_dongle *a, t_dongle *b)
{
    if (a->nb < b->nb)
    {
        pthread_mutex_lock(&a->mutex);
        pthread_mutex_lock(&b->mutex);
    }
    else
    {
        pthread_mutex_lock(&b->mutex);
        pthread_mutex_lock(&a->mutex);
    }
}

void unlock_two_dongles(t_dongle *a, t_dongle *b)
{
    pthread_mutex_unlock(&a->mutex);
    pthread_mutex_unlock(&b->mutex);
}

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

int	is_dongle_free(t_dev *dev)
{
	t_dev			*next;
	t_dev			*prev;
	long long	now;

	next = &dev->all_coders[dev->next_dev];
	prev = &dev->all_coders[dev->prev_dev];

	now = get_time();
	if (next->dongle.is_used || now < next->dongle.available_at) 
		return (0);
	if (prev->dongle.is_used || now < prev->dongle.available_at)
		return (0);
	return (1);
}

void	free_dongle(t_dev *dev)
{
	t_dev	*next;
	t_dev	*prev;
	long long	now;

	now = get_time();
	next = &dev->all_coders[dev->next_dev];
	prev = &dev->all_coders[dev->prev_dev];
	next->dongle.is_used = false;
	prev->dongle.is_used = false;
	next->dongle.available_at = now + next->dongle.cooldown;
	prev->dongle.available_at = now + prev->dongle.cooldown;
	pthread_cond_broadcast(&next->dongle.cond);
	pthread_cond_broadcast(&prev->dongle.cond);
}
