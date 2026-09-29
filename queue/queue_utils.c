/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 17:01:54 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/29 17:09:14 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void disable_node(t_node *node)
{
  if (node && node->dev_id >= 0)
    node->dev_id = - (node->dev_id) + 1;
}

int get_original_id(t_node *node)
{
  if (!node)
    return (-1);
  if (node->dev_id < 0)
    return (-(node->dev_id)-1);
  return (node->dev_id);
}

void enable_node(t_node *node)
{
  if (node && node->dev_id < 0)
    node->dev_id = -(node->dev_id) - 1;
}
