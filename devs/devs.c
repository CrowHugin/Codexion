/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:23:45 by bastien           #+#    #+#             */
/*   Updated: 2026/08/29 00:01:30 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"

void	set_up_dev(t_dev *coders, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		coders[i].nb = i + 1;
		coders[i].has_doggle = 1;
		coders[i].state = STATE_DEBUG;
		i++;
	}
}

