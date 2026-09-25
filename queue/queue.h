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
# include "../devs/dev.h"

typedef struct s_node	t_node;

typedef struct s_node
{
	int			dev_id;
	t_node		*next;
	long		deadline;
}	t_node;

void	enqueue(t_dongle *d, int coder_id, long long deadline);
void	dequeue(t_dongle *d, int coder_id);
int		in_queue(t_dongle *d, int coder_id);
int		is_top(t_dongle *d, int coder_id, int scheduler);

#endif
