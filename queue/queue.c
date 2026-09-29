/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:02 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:50:04 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "../devs/dev.h"
#include <stdlib.h>

t_node  *new_node(t_node **queue, int coder_id, t_dev *coders)
{
  t_dev coder;
  t_node  *node;
  t_node  *tmp;
  int deadline;

  if (!queue || !coders)
    return (NULL);

  node = (t_node *)malloc(sizeof(t_node));
  if (!node)
    return (NULL);

  coder = coders->all_coders[coder_id];
  deadline = coder.last_compile_time + coder.options->timeToBurnout;
  node->dev_id = coder_id;
  node->coders = coders;
  node->next = NULL;
  node->deadline = deadline;

  if (!*queue)
  {
    *queue = node;
    return (node);
  }
  tmp = *queue;
  while (tmp != NULL)
    tmp = tmp->next;
  tmp->next = node;
  return node;
}

void switch_value(t_node **queue, t_node *node_1, t_node *node_2)
{
  int tmp_id;
  long long tmp_deadline;

  tmp_id = node_1->dev_id;
  tmp_deadline = node_1->deadline;
  node_1->dev_id = node_2->dev_id;
  node_1->deadline = node_2->deadline;
  node_2->dev_id = tmp_id;
  node_2->deadline = tmp_deadline;
}

int switch_nodes(t_node **queue, int coder_id_1, int coder_id_2)
{
  t_node *tmp;
  t_node *node_1;
  t_node *node_2;

  node_1 = NULL;
  node_2 = NULL;
  if (!queue || !coder_id_1 || !coder_id_2)
    return (1);
  tmp = *queue;
  while (tmp != NULL)
  {
    if (tmp->dev_id == coder_id_1)
      node_1 = tmp;
    if (tmp->dev_id == coder_id_2)
      node_2 = tmp;
    tmp = tmp->next;
  }
  if (!node_1 || !node_2)
    return (1);
  switch_value(queue, node_1, node_2);
}

int move_to_last(t_node **queue, t_node *node)
{
  t_node  *curr;
  t_node  *prev;
  t_node  *last;

  if (!queue || !*queue || !node || !node->next)
    return (0);
  curr = *queue;
  prev = NULL;
  while (curr && curr != node)
  {
    prev = curr;
    curr = curr->next;
  }
  if (!curr)
    return (1);
  if (prev == NULL)
    *queue = curr->next;
  else 
    prev->next = curr->next;
  last = *queue;
  while(last->next != NULL)
    last = last->next;
  last->next = curr;
  curr->next = NULL;
}

int free_queue(t_node **queue)
{
  t_node  *tmp;
  t_node  *next;

  if (!queue || !*queue)
    return (1);
  tmp = *queue;
  while (tmp != NULL)
  {
    next = tmp->next;
    free(tmp);
    tmp = next;
  }
  *queue = NULL;
  return (0);
}

int free_node(t_node **queue, t_node node)
{
  t_node  *tmp;

  tmp = *queue;
  while (tmp)
  {
    if (tmp->dev_id == node.dev_id)
    {
      tmp->dev_id = -1;
      tmp->next = NULL;
    }
    tmp = tmp->next;
  }
}

int	isTop(t_node **queue, int coder_id, int scheduler)
{
	int	best;
	int	i;

	best = 0;
	i = 1;
	if (prev->count == 0)
		return (1);
	while (i < prev->count)
	{
		if (scheduler == 0
			&& prev->node[i].arrival < prev->node[best].arrival)
			best = i;
		else if (scheduler == 1
			&& (prev->node[i].deadline < prev->node[best].deadline
				|| (prev->node[i].deadline == prev->node[best].deadline
					&& prev->node[i].arrival < prev->node[best].arrival)))
			best = i;
		i++;
	}
	return (prev->node[best].dev_id == coder_id);
}
