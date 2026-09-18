/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:51:19 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:51:20 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../devs/dev.h"
#include <stdio.h>
#include <stdlib.h>

void	create_thread(t_dev *coders, int len, int *queue)
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
		if (res)
		{
			printf("Error while creating thread\nAborting...\n");
			exit(1);
		}
		i++;
	}
}

int	close_threads(t_dev *coders, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}
	return (0);
}
