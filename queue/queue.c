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

#include "../devs/dev.h"
#include <stdlib.h>

int is_in_queue(t_node *queue, int coder_id)
{
  t_node *tmp;

  tmp = queue;
  while (tmp)
  {
    if (tmp->dev_id == coder_id)
      return (1);
    tmp = tmp->next;
  }
  return (0);
}

t_node  *new_node(t_node **queue, int coder_id, t_dev coders)
{
  t_dev coder;
  t_node  *new_node;
  int deadline;

  coder = coders.all_coders[coder_id];
  deadline = coder.last_compile_time + coder.options->timeToBurnout;
  new_node = (t_node *)malloc(sizeof(t_node));
  if (!new_node)
    return (NULL);
  new_node->dev_id = coder_id;
  new_node->next = NULL;
  new_node->deadline = deadline;
}

int add_to_queue(t_node **queue, t_node *node, int coder_id)
{
  t_node *tmp;

  if (is_in_queue(*queue, coder_id))
    return (1);
  if (!queue || !coder_id)
    return (1);
  tmp = *queue;
  while (tmp)
    tmp = tmp->next;
  tmp->next = node;
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
