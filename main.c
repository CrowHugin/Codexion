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
#include "queue/queue.h"
#include "devs/dev.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdatomic.h>

int setup(t_dev **coders, t_node **queue, t_options options)
{
	coders = malloc(sizeof(t_dev) * options.nbCoders);
	queue = malloc(sizeof(t_node) * options.nbCoders);
  if (!coders || !queue)
  {
    free(coders);
    free(queue);
    return (1);
  }
  return (0);
}

void  close(t_options *options, t_dev *coders, t_node *queue)
{
	close_threads(coders, options->nbCoders);
	for (int i = 0; i < options->nbCoders; i++)
	{
		pthread_mutex_destroy(&coders[i].dongle.mutex);
		free(coders[i].dongle.node);
	}
  free(coders);
	free(queue);
}

int	main(int argc, char *argv[])
{
	t_options	options;
	t_dev			*coders;
	t_node		*queue;
	atomic_int		keep_running;
	pthread_mutex_t	lock;


	atomic_init(&keep_running, 1);
	pthread_mutex_init(&lock, NULL);
	if (parsing(argc, argv, &options) != 0)
		return (1);
  if (setup(&coders, &queue, options) != 0)
    return (1);
	set_up_dev(&options, coders, queue, &keep_running, &lock);
	create_thread(coders, options.nbCoders);
	monitoring(coders);
  close(&options, coders, queue);
}
