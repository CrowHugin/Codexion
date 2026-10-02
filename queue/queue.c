/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:02 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/29 17:10:15 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "../devs/dev.h"
#include <stdlib.h>
#include <string.h>

t_node  *new_node(t_node **queue, int coder_id, t_dev *coders)
{
  t_node  *node;
  t_node  *tmp;
  t_dev   dev;
  long long deadline;

  if (!queue || !coders)
    return (NULL);

  node = (t_node *)malloc(sizeof(t_node));
  if (!node)
    return (NULL);
  pthread_cond_init(&node->cond, NULL);
	if (coders[coder_id - 1].options)
  {
    dev = coders[coder_id - 1];
		deadline = dev.last_compile_time + dev.options->timeToBurnout;
  }
	else
		deadline = 0;
  node->dev_id = -(coder_id);
  node->coders = coders;
  node->next = NULL;
  node->deadline = deadline;
  if (!*queue)
  {
    *queue = node;
    return (node);
  }
  tmp = *queue;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = node;
  return node;
}

int move_to_last(t_node **queue, t_node *node)
{
  t_node  *curr;
  t_node  *prev;
  t_node  *last;

  if (!queue || !*queue || !node || (*queue)->next == NULL)
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
  if (curr->next == NULL)
    return (0);
  if (prev == NULL)
    *queue = curr->next;
  else 
    prev->next = curr->next;
  last = *queue;
  while(last->next != NULL)
    last = last->next;
  last->next = curr;
  curr->next = NULL;
  return (0);
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
    pthread_cond_destroy(&tmp->cond);
    free(tmp);
    tmp = next;
  }
  *queue = NULL;
  return (0);
}

int is_top(t_node **queue, int coder_id, t_options *options)
{
    t_node  *curr;
    t_node  *best_node;

    if (!queue || !*queue)
        return (0);
    curr = *queue;
    best_node = NULL;
    if (strcmp(options->scheduler, "fifo") == 0)
    {
        while (curr)
        {
            if (curr->dev_id < 0)
                return (curr->dev_id == -coder_id);
            curr = curr->next;
        }
        return (0);
    }

    if (strcmp(options->scheduler, "edf") == 0)
    {
        while (curr)
        {
            if (curr->dev_id < 0)
            {
                if (!best_node)
                    best_node = curr;
                else if (curr->deadline < best_node->deadline)
                    best_node = curr;
            }
            curr = curr->next;
        }

        if (best_node)
            return (best_node->dev_id == -coder_id);
    }
    return (0);
}
