/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 15:28:54 by bkuntz            #+#    #+#             */
/*   Updated: 2026/10/03 15:28:12 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "../devs/dev.h"

int	fifo(t_node **queue, int coder_id)
{
	t_node	*curr;

	curr = *queue;
	while (curr)
	{
		if (curr->dev_id > 0)
			return (curr->dev_id == coder_id);
		curr = curr->next;
	}
	return (0);
}

int	edf(t_node **queue, int coder_id)
{
	t_node	*curr;
	t_node	*best_node;

	best_node = NULL;
	curr = *queue;
	while (curr)
	{
		if (curr->dev_id > 0)
		{
			if (!best_node)
				best_node = curr;
			else if (curr->deadline < best_node->deadline)
				best_node = curr;
		}
		curr = curr->next;
	}
	if (best_node)
		return (best_node->dev_id == coder_id);
	return (0);
}
