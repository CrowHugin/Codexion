/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 23:24:43 by bastien           #+#    #+#             */
/*   Updated: 2026/09/13 19:30:49 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "../devs/dev.h"

int	in_queue(t_dongle *d, int coder_id)
{
	int	i;

	i = 0;
	while (i < d->count)
	{
		if (d->waiters[i].dev_id == coder_id)
			return (1);
		i++;
	}
	return (0);
}

void	enqueue(t_dongle *d, int coder_id, long long deadline)
{
	if (in_queue(d, coder_id) || d->count >= d->cap)
		return ;
	d->waiters[d->count].dev_id = coder_id;
	d->waiters[d->count].arrival = get_time();
	d->waiters[d->count].deadline = deadline;
	d->count++;
}

void	dequeue(t_dongle *d, int coder_id)
{
	int	i;

	i = 0;
	while (i < d->count)
	{
		if (d->waiters[i].dev_id == coder_id)
		{
			d->waiters[i] = d->waiters[d->count - 1];
			d->count--;
			return ;
		}
		i++;
	}
}

int	is_top(t_dongle *d, int coder_id, int scheduler)
{
	int	best;
	int	i;

	best = 0;
	i = 1;
	if (d->count == 0)
		return (1);
	while (i < d->count)
	{
		if (scheduler == 0
			&& d->waiters[i].arrival < d->waiters[best].arrival)
			best = i;
		else if (scheduler == 1
			&& (d->waiters[i].deadline < d->waiters[best].deadline
				|| (d->waiters[i].deadline == d->waiters[best].deadline
					&& d->waiters[i].arrival < d->waiters[best].arrival)))
			best = i;
		i++;
	}
	return (d->waiters[best].dev_id == coder_id);
}
