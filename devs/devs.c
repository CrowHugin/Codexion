/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:27 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:50:29 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
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
		coders[i].thread_lock = thread_lock;
		coders[i].dongle.waiters = malloc(sizeof(t_request) * options[0]);
		coders[i].dongle.count = 0;
		coders[i].dongle.cap = options[0];
		coders[i].dongle.available_at = 0;
		coders[i].dongle.is_used = false;
		pthread_mutex_init(&coders[i].dongle.mutex, NULL);
		pthread_cond_init(&coders[i].dongle.cond, NULL);
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
	t_dongle	*prev_d;
	t_dongle	*next_d;
	t_dongle	*a;
	t_dongle	*b;
	long long	deadline;
	t_dongle	*tmp;

	if (dev->state == 0)
	{
		prev_d = &dev->all_coders[dev->prev_dev].dongle;
		next_d = &dev->all_coders[dev->next_dev].dongle;
		deadline = dev->last_compile_time + dev->options[1];
		a = prev_d;
		b = next_d;
		if (a->nb > b->nb)
		{
			tmp = a;
			a = b;
			b = tmp;
		}
		acquire_dongle(dev, a, dev->nb, deadline, dev->options[7], start_time);
		if (atomic_load(dev->keep_running) == 0)
			return ;
		acquire_dongle(dev, b, dev->nb, deadline, dev->options[7], start_time);
		if (atomic_load(dev->keep_running) == 0)
			return ;
		take_dongle(dev, get_time() - start_time);
		dev->state = 1;
		dev->last_compile_time = get_time();
		printf("%llu %d is compiling\n", get_time() - start_time, dev->nb);
		usleep(dev->options[2]);
		release_dongle(prev_d, prev_d->cooldown);
		release_dongle(next_d, next_d->cooldown);
		(*ind)++;
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
	coders->last_compile_time = start_time;
	while (i < coders->options[5] && atomic_load(coders->keep_running) == true)
		change_state(coders, start_time, &i);
	if (atomic_load(coders->keep_running) == true)
		coders->state = STATE_FINNISH;
	return (NULL);
}
