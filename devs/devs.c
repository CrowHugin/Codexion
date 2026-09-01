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
#include <unistd.h>
#include <sys/time.h>

void	set_up_dev(t_dev *coders, int *options, int *queue)
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
		coders[i].burnout_delay = 0;
		coders[i].dongle.nb = i + 1;
		coders[i].dongle.is_used = false;
		coders[i].dongle.cooldown = options[6];
		i++;
	}
}

void check_burnout(t_dev *dev, bool *flag, long long start_time)
{
	if (dev->burnout_delay >= dev->options[1])
	{
		*flag = true;
		printf("%llu %d burned out\n", get_time() - start_time, dev->nb);
	}
}

void	change_state(t_dev *dev, long long start_time, bool *flag)
{
	if (dev->state == 0)
	{
		dev->state = 1;
		if (is_dongle_free(dev))
		{
			printf("%llu %d is compiling\n", get_time() - start_time, dev->nb);
			dev->burnout_delay = 0;
			usleep(dev->options[2]);
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
	check_burnout(dev, flag, start_time);
	dev->burnout_delay += get_time() - start_time;
}

void	*dev_behaivor(void *arg)
{
	long long	start_time;
	t_dev	*coders;
	int		i;
	bool	flag_stop;

	flag_stop = false;

	start_time = get_time();
	coders = (t_dev *)arg;
	i = 0;
	while (i < coders->options[5] && flag_stop == false)
	{
		change_state(coders, start_time, &flag_stop);
		i++;
	}
	return (NULL);
}
