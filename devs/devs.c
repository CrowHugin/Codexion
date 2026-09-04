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
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void	set_up_dev(t_dev *coders, 
								 int *options, 
								 int *queue,
								 int *ptr_running,
								 pthread_mutex_t *thread_lock)
{
	int		i;

	i = 0;
	while (i < options[0])
	{
		coders[i].nb = i + 1;
		coders[i].state = STATE_DEBUG;
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
		i++;
	}
}

void check_burnout(t_dev *dev, long long start_time)
{
	if (*(dev->keep_running) == false)
		return ;	
	pthread_mutex_lock(dev->thread_lock);
	if (get_time() - dev->last_compile_time >= dev->options[1])
	{
		*(dev->keep_running) = false;
		dev->state = STATE_BURNOUT;
		printf("%llu %d burned out\n", get_time() - start_time, dev->nb);
	}
	pthread_mutex_unlock(dev->thread_lock);
}

void	change_state(t_dev *dev, long long start_time, int *ind)
{
	if (dev->state == 0)
	{
		if (is_dongle_free(dev))
		{
			pthread_mutex_lock(dev->thread_lock);
			dev->state = 1;
			printf("%llu %d is compiling\n", get_time() - start_time, dev->nb);
			dev->last_compile_time += get_time();
			usleep(dev->options[2]);
			dev->last_compile_time += get_time();
			(*ind)++;
			free_dongle(dev);
			pthread_mutex_unlock(dev->thread_lock);
		}
		usleep(dev->options[2]);
	}
	else if (dev->state == 1)
	{
		pthread_mutex_lock(dev->thread_lock);
		dev->state = 2;
		printf("%llu %d is debugging\n", get_time() - start_time, dev->nb);
		usleep(dev->options[3]);
		pthread_mutex_unlock(dev->thread_lock);
	}
	else if (dev->state == 2)
	{
		pthread_mutex_lock(dev->thread_lock);
		dev->state = 0;
		printf("%llu %d is refactoring\n", get_time() - start_time, dev->nb);
		usleep(dev->options[4]);
		pthread_mutex_unlock(dev->thread_lock);
	}
	check_burnout(dev, start_time);
	usleep(10);
}

void	*dev_behaivor(void *arg)
{
	long long	start_time;
	t_dev	*coders;
	int		i;

	start_time = get_time();
	coders = (t_dev *)arg;
	i = 0;
	while (i < coders->options[5] && *(coders->keep_running) == true)
		change_state(coders, start_time, &i);
	return (NULL);
}
