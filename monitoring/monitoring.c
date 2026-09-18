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

void	monitoring(t_dev *coders)
{
	int	i;
	int	total_coders;
	int	done;

	done = 0;
	total_coders = coders[0].options[0];
	while (true)
	{
		i = 0;
		while (i < total_coders)
		{
			if (coders[i].state == STATE_BURNOUT
				|| coders[i].state == STATE_FINNISH)
				done++;
			i++;
		}
		if (done == total_coders)
			return ;
		usleep(10);
	}
}
	// // testing the queue
	// int	queue_size;
	// queue_size = 0;
	// for (int i = 0; i < options[0]; i++)
	// 	add_queue(&coders->queue, &queue_size, coders[i].nb);
	// // print_queue(queue, queue_size);
	// pop_queue(&coders->queue, &queue_size, 1);
	// // print_queue(queue, queue_size);
// 	return (0);
// }
