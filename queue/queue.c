/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 23:24:43 by bastien           #+#    #+#             */
/*   Updated: 2026/08/29 23:25:14 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int	init_queue(t_node **queue, int nb_dev)
{
	*queue = calloc(nb_dev, sizeof(t_node));
	if (!(*queue))
		return (1);
	return (0);
}

void addBack(t_node **queue, t_node *a)
{
	t_node *tmp;

	if (!*queue || !a)
		return;
	tmp = *queue;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = a;
}

int	peek(t_node *queue)
{
	if (!queue)
		return (-1);
	return (queue->dev_id);
}

int	getIndexToPop(t_node *queue, int scheduler)
{
	int			ind;
	t_node	*tmp;
	long		deadline;

	tmp = queue;
	// FIFO
	if (scheduler == 0)
	{
		ind = queue->dev_id;
		while (tmp->next)
		{
			if (tmp->dev_id > ind)
				ind = tmp->dev_id;
		}
		return ind;
	}
	// EDF
	deadline = tmp->deadline;
	while (tmp->next)
	{
		if (tmp->deadline < deadline)
			ind = tmp->dev_id;
	}
	return (ind);
}

// void popQueue(t_node **queue, int indPop)
// {
// 	t_node *tmp;
// 
// 	while (tmp->dev_id != indPop)
// 		tmp = tmp->next
// }
