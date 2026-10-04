/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:42 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:50:43 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	wait(t_dev *dev, t_node *curr)
{
	struct timespec	ts;
	long long		target_ms;

	pthread_mutex_lock(dev->thread_lock);
	if (atomic_load(dev->keep_running) == 1)
	{
		target_ms = get_time() + 1;
		ts.tv_sec = target_ms / 1000;
		ts.tv_nsec = (target_ms % 1000) * 1000000LL;
		pthread_cond_timedwait(&curr->cond, dev->thread_lock, &ts);
	}
	pthread_mutex_unlock(dev->thread_lock);
}

void	compile(t_dev *dev, t_node *curr, int *ind, long long start_time)
{
	pthread_mutex_lock(dev->thread_lock);
	dev->state = 1;
	dev->last_compile_time = get_time();
	stop_wait(curr);
	update_node_deadline(dev->queue, dev->nb, dev->last_compile_time
		+ dev->options->time_to_burnout);
	pthread_mutex_unlock(dev->thread_lock);
	printf("%llu %d is compiling\n", get_time() - start_time, dev->nb);
	usleep(dev->options->time_to_compile);
	release_dongles(dev);
	(*ind)++;
}

void	debug(t_dev *dev, long long start_time)
{
	usleep(dev->options->time_to_debug);
	pthread_mutex_lock(dev->thread_lock);
	dev->state = 2;
	printf("%llu %d is debugging\n", get_time() - start_time, dev->nb);
	pthread_mutex_unlock(dev->thread_lock);
}

void	refactoring(t_dev *dev, long long start_time, t_node *curr)
{
	usleep(dev->options->time_to_refactor);
	pthread_mutex_lock(dev->thread_lock);
	printf("%llu %d is refactoring\n", get_time() - start_time, dev->nb);
	dev->state = 0;
	enable_wait(curr);
	move_to_last(dev->queue, curr);
	pthread_mutex_unlock(dev->thread_lock);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (milliseconds);
}
