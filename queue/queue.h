/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 23:25:35 by bastien           #+#    #+#             */
/*   Updated: 2026/10/03 15:28:15 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include <pthread.h>

typedef struct s_node		t_node;
typedef struct s_options	t_options;
typedef struct s_developper	t_dev;

typedef struct s_node
{
	pthread_cond_t	cond;
	t_node			*next;
	long			deadline;
	t_dev			*coders;
	int				dev_id;
}	t_node;

t_node	*new_node(t_node **queue, int coder_id, t_dev *coders);
int		switch_nodes(t_node **queue, int coder_id_1, int coder_id_2);
void	stop_wait(t_node *node);
void	enable_wait(t_node *node);
int		free_queue(t_node **queue);
void	update_node_deadline(t_node **queue, int coder_id,
			long long new_deadline);
int		is_top(t_node **queue, int coder_id, t_options *options);
int		move_to_last(t_node **queue, t_node *node);

#endif
