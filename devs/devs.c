/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:27 by bkuntz            #+#    #+#             */
/*   Updated: 2026/10/03 16:15:10 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void	set_up_dev(t_options *options,
								t_dev *coders,
								t_node **queue,
								atomic_int	*ptr_running,
								pthread_mutex_t *thread_lock)
{
	long long	start_time;
	int			i;

	start_time = get_time();
	i = 0;
	while (i < options->nb_coders)
	{
		coders[i].nb = i + 1;
		coders[i].state = 0;
		coders[i].all_coders = coders;
		coders[i].queue = queue;
		coders[i].next_dev = (i + 1) % options->nb_coders;
		coders[i].prev_dev = (i + options->nb_coders - 1) % options->nb_coders;
		coders[i].last_compile_time = start_time;
		coders[i].options = options;
		coders[i].keep_running = ptr_running;
		coders[i].thread_lock = thread_lock;
		coders[i].dongle.nb = i + 1;
		coders[i].dongle.is_used = false;
		coders[i].dongle.cooldown = options->dongle_cooldown;
		coders[i].dongle.available_at = 0;
		coders[i].dongle.is_used = false;
		pthread_mutex_init(&coders[i].dongle.mutex, NULL);
		pthread_cond_init(&coders[i].dongle.cond, NULL);
		i++;
	}
}

void	change_state(t_dev *dev, long long start_time, int *ind)
{
	t_node			*tmp;

	tmp = *(dev->queue);
	while (tmp != NULL && tmp->dev_id != dev->nb && tmp->dev_id != -dev->nb)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (dev->state == 0)
	{
		if (take_dongle(dev, start_time) == 1)
			wait(dev, tmp);
		else
			compile(dev, tmp, ind, start_time);
	}
	else if (dev->state == 1)
		debug(dev, start_time);
	else if (dev->state == 2)
		refactoring(dev, start_time, tmp);
}

void	*dev_behaivor(void *arg)
{
	long long	start_time;
	t_dev		*coders;
	int			i;

	start_time = get_time();
	coders = (t_dev *)arg;
	i = 0;
	while (i < coders->options->nb_of_compiles_required
		&& atomic_load(coders->keep_running) == true)
		change_state(coders, start_time, &i);
	pthread_mutex_lock(coders->thread_lock);
	if (atomic_load(coders->keep_running) == true)
		coders->state = STATE_FINNISH;
	pthread_mutex_unlock(coders->thread_lock);
	return (NULL);
}
