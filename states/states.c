/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:21:15 by bastien           #+#    #+#             */
/*   Updated: 2026/08/30 00:29:15 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../devs/dev.h"
#include <stdio.h>

void	*change_state(void *arg)
{
	t_dev	*dev;
	char	*state_name[3];

	state_name[0] = "STATE_COMPILE";
	state_name[1] = "STATE_DEBUG";
	state_name[2] = "STATE_REFACTOR";
	dev = (t_dev *)arg;
	if (dev->state == 0)
	{
		dev->state = 1;
		printf("dev nb°%d -> %s\n", dev->nb, state_name[dev->state]);
	}
	else if (dev->state == 1)
	{
		dev->state = 2;
		printf("dev nb°%d -> %s\n", dev->nb, state_name[dev->state]);
	}
	else if (dev->state == 2)
	{
		dev->state = 0;
		printf("dev nb°%d -> %s\n", dev->nb, state_name[dev->state]);
	}
	return (NULL);
}
