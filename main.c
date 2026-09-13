/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:27:27 by bastien           #+#    #+#             */
/*   Updated: 2026/08/29 00:08:53 by bastien          ###   ########.fr       */
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
	t_dev			*coders;
	int				*options;
	int				*queue;
	atomic_int		keep_running;
	pthread_mutex_t	lock;

	atomic_init(&keep_running, 1);
	pthread_mutex_init(&lock, NULL);
	options = malloc(sizeof(int) * argc + 1);
	queue = NULL;
	if (!options)
		return (1);
	if (parsing(argc, argv, options))
	{
		free(options);
		return (1);
	}
	coders = malloc(sizeof(t_dev) * options[0]);
	if (!coders)
		return (1);
	set_up_dev(coders, options, queue, &keep_running, &lock);
	create_thread(coders, options[0], coders->queue);
	monitoring(coders);
	close_threads(coders, options[0]);
	for (int i = 0; i < options[0]; i++)
	{
		pthread_mutex_destroy(&coders[i].dongle.mutex);
		free(coders[i].dongle.waiters);
	}
	free(queue);
	free(options);
	free(coders);
}
