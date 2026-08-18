/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:23:45 by bastien           #+#    #+#             */
/*   Updated: 2026/08/18 17:13:29 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <stdlib.h>

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
	free(coders);
	return (0);
}
