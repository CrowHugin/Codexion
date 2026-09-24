/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:49:47 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:49:50 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../devs/dev.h"
#include <unistd.h>

void	monitoring(t_dev *coders)
{
	int	i;
	int	total_coders;
	int	done;

	done = 0;
	total_coders = coders[0].options->nbCoders;
	while (true)
	{
		i = 0;
		while (i < total_coders)
		{
			if (coders[i].state == STATE_BURNOUT
				|| coders[i].state == STATE_FINNISH)
				done++;
			i++;
		}
		if (done == total_coders)
			return ;
		usleep(10);
	}
}
