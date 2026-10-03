/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 17:01:54 by bkuntz            #+#    #+#             */
/*   Updated: 2026/10/03 15:28:12 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	stop_wait(t_node *node)
{
	if (node && node->dev_id > 0)
		node->dev_id = -node->dev_id;
}

void	enable_wait(t_node *node)
{
	if (node && node->dev_id < 0)
		node->dev_id = -node->dev_id;
}

void	update_node_deadline(t_node **queue, int coder_id,
													long long new_deadline)
{
	t_node	*tmp;

	if (!queue || !*queue)
		return ;
	tmp = *queue;
	while (tmp)
	{
		if (tmp->dev_id == -coder_id || tmp->dev_id == coder_id)
		{
			tmp->deadline = new_deadline;
			break ;
		}
		tmp = tmp->next;
	}
}

t_node	*find_node(t_node **queue, t_node *node)
{
	t_node	*curr;
	t_node	*prev;

	curr = *queue;
	prev = NULL;
	while (curr && curr != node)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr || curr->next == NULL)
		return (NULL);
	if (prev == NULL)
		*queue = curr->next;
	else
		prev->next = curr->next;
	return (curr);
}
