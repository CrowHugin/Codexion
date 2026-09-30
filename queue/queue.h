/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 23:25:35 by bastien           #+#    #+#             */
/*   Updated: 2026/08/29 23:27:38 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

typedef struct s_node	t_node;
typedef struct s_options	t_options;
typedef struct s_developper t_dev;

typedef struct s_node
{
	int			dev_id;
  t_dev     *coders;
	t_node		*next;
	long		deadline;
}	t_node;

t_node  *new_node(t_node **queue, int coder_id, t_dev *coders);
int switch_nodes(t_node **queue, int coder_id_1, int coder_id_2);
void stp_wait(t_node *node);
int get_original_id(t_node *node);
void enable_wait(t_node *node);
int free_queue(t_node **queue);
void	update_node_deadline(t_node **queue, int coder_id, 
		long long new_deadline);
int is_top(t_node **queue, int coder_id, t_options *options);

#endif
