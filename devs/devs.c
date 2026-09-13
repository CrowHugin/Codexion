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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void	set_up_dev(t_dev *coders,
								int	*options,
								int *queue,
								atomic_int	*ptr_running,
								pthread_mutex_t *thread_lock)
{
	int		i;

	i = 0;
	while (i < options[0])
	{
		coders[i].nb = i + 1;
		coders[i].state = 0;
		coders[i].all_coders = coders;
		coders[i].queue = queue;
		coders[i].next_dev = (i + 1) % options[0];
		coders[i].prev_dev = (i + options[0] - 1) % options[0];
		coders[i].options = options;
		coders[i].keep_running = ptr_running;
		coders[i].dongle.nb = i + 1;
		coders[i].dongle.is_used = false;
		coders[i].dongle.cooldown = options[6];
		coders[i].last_compile_time = get_time();
		coders[i].thread_lock = thread_lock;
		pthread_mutex_init(&coders[i].dongle.mutex, NULL);
		i++;
	}
}

void	check_burnout(t_dev *dev, long long start_time)
{
	if (atomic_load(dev->keep_running) == 0)
		return ;
	if (get_time() - dev->last_compile_time >= dev->options[1])
	{
		atomic_store(dev->keep_running, 0);
		pthread_mutex_lock(dev->thread_lock);
		dev->state = STATE_BURNOUT;
		printf("%llu %d burned out\n", get_time() - start_time, dev->nb);
		pthread_mutex_unlock(dev->thread_lock);
	}
}

void	change_state(t_dev *dev, long long start_time, int *ind)
{
	if (dev->state == 0)
	{
		t_dongle	*prev_d = &dev->all_coders[dev->prev_dev].dongle;
		t_dongle	*next_d = &dev->all_coders[dev->next_dev].dongle;

		lock_two_dongles(prev_d, next_d);
		if (is_dongle_free(dev))
		{
			take_dongle(dev, get_time() - start_time);
			dev->state = 1;
			printf("%llu %d is compiling\n", get_time() - start_time, dev->nb);
			dev->last_compile_time = get_time();
			unlock_two_dongles(prev_d, next_d);
			usleep(dev->options[2]);
			lock_two_dongles(prev_d, next_d);
			(*ind)++;
			free_dongle(dev);
			unlock_two_dongles(prev_d, next_d);
		}
		else
		{
			// pthread_cond_wait(&prev_d->cond, &next_d->mutex);
			unlock_two_dongles(prev_d, next_d);
			usleep(200);
		}
	}
	else if (dev->state == 1)
	{
		dev->state = 2;
		printf("%llu %d is debugging\n", get_time() - start_time, dev->nb);
		usleep(dev->options[3]);
	}
	else if (dev->state == 2)
	{
		dev->state = 0;
		printf("%llu %d is refactoring\n", get_time() - start_time, dev->nb);
		usleep(dev->options[4]);
	}
	check_burnout(dev, start_time);
}

void	*dev_behaivor(void *arg)
{
	long long	start_time;
	t_dev		*coders;
	int			i;

	start_time = get_time();
	coders = (t_dev *)arg;
	i = 0;
	while (i < coders->options[5] && atomic_load(coders->keep_running) == true)
		change_state(coders, start_time, &i);
	return (NULL);
}
