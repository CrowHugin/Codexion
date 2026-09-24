/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:49:27 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:49:31 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "monitoring/monitoring.h"
#include "threads/threads.h"
#include "devs/dev.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdatomic.h>

int	main(int argc, char *argv[])
{
	t_options	options;
	t_dev			*coders;
	atomic_int		keep_running;
	pthread_mutex_t	lock;
	int				*queue;


	atomic_init(&keep_running, 1);
	pthread_mutex_init(&lock, NULL);
	queue = NULL;
	if (parsing(argc, argv, &options) != 0)
		return (1);
	coders = malloc(sizeof(t_dev) * options.nbCoders);
	set_up_dev(&options, coders, queue, &keep_running, &lock);
	create_thread(coders, options.nbCoders, coders->queue);
	monitoring(coders);
	close_threads(coders, options.nbCoders);
	for (int i = 0; i < options.nbCoders; i++)
	{
		pthread_mutex_destroy(&coders[i].dongle.mutex);
		free(coders[i].dongle.node);
	}
	free(queue);
}
