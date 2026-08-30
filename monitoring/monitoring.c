/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:35:22 by bastien           #+#    #+#             */
/*   Updated: 2026/08/30 00:49:29 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../devs/dev.h"
#include "../errors/errors.h"
#include "../queue/queue.h"
#include <stdlib.h>

int	create_thread(t_dev *coders, int len, int *queue)
{
	int	i;
	int	res;

	(void)queue;
	i = 0;
	while (i < len)
	{
		res = pthread_create(&coders[i].thread,
				NULL,
				dev_behaivor,
				(void *)&coders[i]);
		if (res != 0)
			print_error(g_err.err_4);
		i++;
	}
	i = 0;
	while (i < len)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}
	return (0);
}

int	monitoring(t_dev *coders, int *options)
{
	int	*queue;
	int	queue_size;

	queue = NULL;
	queue_size = 0;
	create_thread(coders, options[0], queue);
	// testing
	for (int i = 0; i < options[0]; i++)
		add_queue(&queue, &queue_size, coders[i].nb);
	print_queue(queue, queue_size);
	pop_queue(&queue, &queue_size, 1);
	print_queue(queue, queue_size);
	free(queue);
	return (0);
}
