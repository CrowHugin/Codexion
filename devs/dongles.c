/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:52 by bkuntz            #+#    #+#             */
/*   Updated: 2026/10/03 15:17:45 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	set_importance(t_dev *next, t_dev *prev, t_dev **first, t_dev **second)
{
	if (next->nb < prev->nb)
	{
		*first = next;
		*second = prev;
	}
	else
	{
		*first = prev;
		*second = next;
	}
}

void	send_signal(t_dev *coder)
{
	t_node		*curr;

	curr = *(coder->queue);
	while (curr)
	{
		pthread_cond_signal(&curr->cond);
		curr = curr->next;
	}
}

int	dongle(t_dev *first, t_dev *second, long long start, t_dev *coder)
{
	long long	time;

	time = get_time();
	if (first->dongle.is_used == false && second->dongle.is_used == false
		&& time >= first->dongle.available_at
		&& time >= second->dongle.available_at)
	{
		first->dongle.is_used = true;
		second->dongle.is_used = true;
		printf("%llu %d has taken a dongle\n", time - start, coder->nb);
		printf("%llu %d has taken a dongle\n", time - start, coder->nb);
		return (0);
	}
	return (1);
}

int	take_dongle(t_dev *coder, long long start)
{
	t_dev		*next_dev;
	t_dev		*prev_dev;
	t_dev		*first;
	t_dev		*second;
	int			status;

	pthread_mutex_lock(coder->thread_lock);
	if (!is_top(coder->queue, coder->nb, coder->options))
	{
		pthread_mutex_unlock(coder->thread_lock);
		return (1);
	}
	pthread_mutex_unlock(coder->thread_lock);
	next_dev = &coder->all_coders[coder->next_dev];
	prev_dev = &coder->all_coders[coder->prev_dev];
	set_importance(next_dev, prev_dev, &first, &second);
	if (first == second)
		return (1);
	pthread_mutex_lock(&first->dongle.mutex);
	pthread_mutex_lock(&second->dongle.mutex);
	status = dongle(first, second, start, coder);
	pthread_mutex_unlock(&second->dongle.mutex);
	pthread_mutex_unlock(&first->dongle.mutex);
	return (status);
}

void	release_dongles(t_dev *coder)
{
	long long	cooldown;
	t_dev		*next_dev;
	t_dev		*prev_dev;
	t_dev		*first;
	t_dev		*second;

	cooldown = coder->options->dongle_cooldown;
	next_dev = &coder->all_coders[coder->next_dev];
	prev_dev = &coder->all_coders[coder->prev_dev];
	set_importance(next_dev, prev_dev, &first, &second);
	if (first != second)
	{
		pthread_mutex_lock(&first->dongle.mutex);
		pthread_mutex_lock(&second->dongle.mutex);
		next_dev->dongle.is_used = false;
		prev_dev->dongle.is_used = false;
		next_dev->dongle.available_at = get_time() + cooldown;
		prev_dev->dongle.available_at = get_time() + cooldown;
		pthread_mutex_unlock(&second->dongle.mutex);
		pthread_mutex_unlock(&first->dongle.mutex);
	}
	pthread_mutex_lock(coder->thread_lock);
	send_signal(coder);
	pthread_mutex_unlock(coder->thread_lock);
}
