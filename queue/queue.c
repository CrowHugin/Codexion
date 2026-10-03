/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:02 by bkuntz            #+#    #+#             */
/*   Updated: 2026/10/03 16:26:59 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "../devs/dev.h"
#include <stdlib.h>
#include <string.h>

t_node	*new_node(t_node **queue, int coder_id, t_dev *coders)
{
	t_node		*node;
	t_node		*tmp;
	t_dev		*dev;

	if (!queue || !coders)
		return (NULL);
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	pthread_cond_init(&node->cond, NULL);
	dev = &coders[coder_id - 1];
	node->dev_id = coder_id;
	node->coders = coders;
	node->next = NULL;
	node->deadline = 0;
	if (dev->options)
		node->deadline = dev->last_compile_time + dev->options->time_to_burnout;
	if (!*queue)
		return (*queue = node);
	tmp = *queue;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	return (node);
}

int	move_to_last(t_node **queue, t_node *node)
{
	t_node	*target;
	t_node	*last;

	if (!queue || !*queue || !node || (*queue)->next == NULL)
		return (0);
	target = find_node(queue, node);
	if (!target)
		return (0);
	last = *queue;
	while (last->next != NULL)
		last = last->next;
	last->next = target;
	target->next = NULL;
	return (0);
}

int	free_queue(t_node **queue)
{
	t_node	*tmp;
	t_node	*next;

	if (!queue || !*queue)
		return (1);
	tmp = *queue;
	while (tmp != NULL)
	{
		next = tmp->next;
		pthread_cond_destroy(&tmp->cond);
		free(tmp);
		tmp = next;
	}
	*queue = NULL;
	return (0);
}

int	is_top(t_node **queue, int coder_id, t_options *options)
{
	if (!queue || !*queue)
		return (0);
	if (strcmp(options->scheduler, "fifo") == 0)
		return (fifo(queue, coder_id));
	if (strcmp(options->scheduler, "edf") == 0)
		return (edf(queue, coder_id));
	return (0);
}
