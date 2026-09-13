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

typedef struct s_node t_node;

typedef struct s_node
{
	int			dev_id;
	t_node	*prev;
	t_node	*next;
	long		deadline;
} t_node;

int	init_queue(t_node **queue, int nb_dev);
void	add_queue(int **queue, int *current_size, int id_dev);
void	print_queue(int *queue, int length);
void	pop_queue(int **queue, int *length, int ind_pop);

#endif
