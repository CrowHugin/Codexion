/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:52 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:50:54 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int	take_dongle(t_dev *coder, long long start)
{
	t_dev	*next_dev;
	t_dev	*prev_dev;
	t_dev	*first;
	t_dev	*second;
	long long	time;

	pthread_mutex_lock(coder->thread_lock);
	update_node_deadline(&coder->queue, coder->nb,
											 coder->last_compile_time + 
											coder->options->timeToBurnout);
	if (!is_top(&coder->queue, coder->nb, coder->options))
	{
			pthread_mutex_unlock(coder->thread_lock);
			return (1);
	}
    pthread_mutex_unlock(coder->thread_lock);
	time = get_time();
	next_dev = &coder->all_coders[coder->next_dev];
	prev_dev = &coder->all_coders[coder->prev_dev];
	if (next_dev->nb < prev_dev->nb)
	{
		first = next_dev;
		second = prev_dev;
	}
	else
	{
		first = prev_dev;
		second = next_dev;
	}
	pthread_mutex_lock(&first->dongle.mutex);
	pthread_mutex_lock(&second->dongle.mutex);
	if (next_dev->dongle.is_used == false 
			&& prev_dev->dongle.is_used == false
			&& time >= next_dev->dongle.available_at 
			&& time >= prev_dev->dongle.available_at)
	{
		next_dev->dongle.is_used = true;
		prev_dev->dongle.is_used = true;
		printf("%llu %d has taken a dongle\n", time - start, coder->nb);
		printf("%llu %d has taken a dongle\n", time - start, coder->nb);
		pthread_mutex_unlock(&second->dongle.mutex);
		pthread_mutex_unlock(&first->dongle.mutex);
		return (0);
	}
	pthread_mutex_unlock(&second->dongle.mutex);
	pthread_mutex_unlock(&first->dongle.mutex);
	return (1);
}

void	release_dongles(t_dev *coder)
{
	t_dev	*next_dev;
	t_dev	*prev_dev;
	long long cooldown;

	cooldown = coder->options->dongleCooldown;

	next_dev = &coder->all_coders[coder->next_dev];
	prev_dev = &coder->all_coders[coder->prev_dev];
	pthread_mutex_lock(&next_dev->dongle.mutex);
	pthread_mutex_lock(&prev_dev->dongle.mutex);
	next_dev->dongle.is_used = false;
	prev_dev->dongle.is_used = false;
	next_dev->dongle.available_at = get_time() + cooldown;
	prev_dev->dongle.available_at = get_time() + cooldown;
	pthread_mutex_unlock(&next_dev->dongle.mutex);
	pthread_mutex_unlock(&prev_dev->dongle.mutex);
}
