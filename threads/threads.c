/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz </var/spool/mail/bkuntz>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:07:13 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/04 15:07:55 by bkuntz           ###   ########.fr       */
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
