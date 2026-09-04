/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:35:22 by bastien           #+#    #+#             */
/*   Updated: 2026/09/04 15:09:32 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../devs/dev.h"
#include <stdio.h>
#include <unistd.h>

void	monitoring(t_dev *coders)
{
	int i;
	int	total_coders;

	total_coders = coders[0].options[0];
	while (true)
	{
		i = 0;
		while (i < total_coders)
		{
			if (coders[i].state == 3)
				return ;
			printf("Coder %d : state = %d\n", i, coders[i].state);
			i++;
		}
		usleep(1000);
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
