/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:49:47 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:49:50 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../devs/dev.h"
#include <unistd.h>
#include <stdio.h>

void	*monitoring_routine(void *arg)
{
	t_dev	*coders;
	long long	now;
	long long	start_time;
	int				total;
	int				i;
	int				finished;

	coders = (t_dev *)arg;
	total = coders[0].options->nb_coders;
	start_time = get_time();
	while (atomic_load(coders[0].keep_running) == 1)
	{
		finished = 0;
		now = get_time();
		i = 0;
		while (i < total)
		{
			pthread_mutex_lock(coders[i].thread_lock);
			if (coders[i].state != STATE_BURNOUT
				&& coders[i].state != STATE_FINNISH)
			{
				if (now - coders[i].last_compile_time
					>= coders[i].options->time_to_burnout)
				{
					coders[i].state = STATE_BURNOUT;
					atomic_store(coders[i].keep_running, 0);
					printf("%llu %d burned out\n",
						now - start_time, coders[i].nb);
					pthread_mutex_unlock(coders[i].thread_lock);
					return (NULL);
				}
			}
			if (coders[i].state == STATE_BURNOUT
				|| coders[i].state == STATE_FINNISH)
				finished++;
			pthread_mutex_unlock(coders[i].thread_lock);
			i++;
		}
		if (finished == total)
			break ;
		usleep(10000);
	}
	return (NULL);
}
