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
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_dev	*coders;
	int		*options;
	int		*queue;

	options = malloc(sizeof(int) * argc);
	queue = NULL;
	if (!options)
		return (1);
	parsing(argc, argv, options);
	coders = malloc(sizeof(t_dev) * options[0]);
	if (!coders)
		return (1);
	set_up_dev(coders, options, queue);
	create_thread(coders, options[0], coders->queue);
	monitoring(coders);
	close_threads(coders, options[0]);
	free(queue);
	free(options);
	free(coders);
}
