/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:23:45 by bastien           #+#    #+#             */
/*   Updated: 2026/08/18 17:50:49 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <stdlib.h>
#include <stdio.h>
#include "../errors/errors.h"

void *print_hello(void *arg)
{
	(void)arg;
	printf("HELLO\n");
	return NULL;
}

int create_thread(t_dev *coders, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		int res = pthread_create(&coders[i].thread, NULL, print_hello, NULL);
		if (res)
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

int	set_up_dev(int *options)
{
	int		i;
	t_dev	*coders;

	i = 0;
	coders = malloc(sizeof(t_dev) * options[0]);
	if (!coders)
		return (1);
	while (i < options[0])
	{
		coders[i].nb = i + 1;
		coders[i].has_doggle = 1;
		coders[i].state = STATE_DEBUG;
		i++;
	}
	coders[2].has_doggle = 0;
	coders[0].has_doggle = 0;
	print_devs_infos(coders, options[0]);
	create_thread(coders, options[0]);
	free(coders);
	return (0);
}
