/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:49:27 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/29 17:10:21 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "queue/queue.h"
#include "devs/dev.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>
#include "threads/threads.h"
#include "monitoring/monitoring.h"

int	setup(t_dev **coders, t_node **queue, t_options options)
{
	int	i;

	i = 0;
	*coders = malloc(sizeof(t_dev) * options.nbCoders);
	memset(*coders, 0, sizeof(t_dev) * options.nbCoders);
	*queue = NULL;
	if (!*coders)
		return (1);
	while (i < options.nbCoders)
	{
		if (!new_node(queue, i + 1, *coders))
		{
			free_queue(queue);
			free(*coders);
			*coders = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void	close(t_options *options, t_dev *coders, t_node *queue)
{
	int	i;

	i = 0;
	close_threads(coders, options->nbCoders);
	while (i < options->nbCoders)
	{
		pthread_mutex_destroy(&coders[i].dongle.mutex);
		i++;
	}
	free(coders);
	free_queue(&queue);
}

int	main(int argc, char *argv[])
{
	t_options	options;
	t_dev		*coders;
	t_node		*queue;
	pthread_mutex_t	lock;
	atomic_int	keep_running;
	pthread_t	monitoring_thread;

	atomic_init(&keep_running, 1);
	pthread_mutex_init(&lock, NULL);
	if (parsing(argc, argv, &options) != 0)
		return (1);
	if (setup(&coders, &queue, options) != 0)
		return (1);
	set_up_dev(&options, coders, &queue, &keep_running, &lock);
	create_thread(coders, options.nbCoders);
	pthread_create(&monitoring_thread, NULL,
		monitoring_routine, (void *)coders);
	pthread_join(monitoring_thread, NULL);
	close(&options, coders, queue);
	pthread_mutex_destroy(&lock);
}
