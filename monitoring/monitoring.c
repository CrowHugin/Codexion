/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:49:47 by bkuntz            #+#    #+#             */
/*   Updated: 2026/10/03 15:20:47 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../devs/dev.h"
#include <unistd.h>
#include <stdio.h>

void	check_state(t_dev *coder, long long start_time, int *finished)
{
	enum e_state	state;
	long long		time;

	if (atomic_load(coder->keep_running) == 0)
		return ;
	pthread_mutex_lock(coder->thread_lock);
	state = coder->state;
	if (state != STATE_BURNOUT && state != STATE_FINNISH)
	{
		time = get_time();
		if (time - coder->last_compile_time >= coder->options->time_to_burnout)
		{
			coder->state = STATE_BURNOUT;
			atomic_store(coder->keep_running, 0);
			printf("%llu %d burned out\n", time - start_time, coder->nb);
		}
	}
	else
		(*finished)++;
	pthread_mutex_unlock(coder->thread_lock);
}

void	*monitoring_routine(t_dev *coders)
{
	long long	start_time;
	int			i;
	int			finished;

	start_time = get_time();
	while (atomic_load(coders[0].keep_running) == 1)
	{
		finished = 0;
		i = 0;
		while (i < coders[0].options->nb_coders)
		{
			check_state(&coders[i], start_time, &finished);
			i++;
		}
		if (finished == coders[0].options->nb_coders)
			break ;
		usleep(10000);
	}
	return (NULL);
}
