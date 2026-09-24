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

// int isInQueue(t_dongle *prev, t_dongle *next, int coder_id)
// {
//   int i;
// 
//   i = 0;
//   while (i < prev->count)
//   {
//     if (prev->node[i].dev_id == coder_id && next->node[i].dev_id == coder_id)
//       return (1);
//   }
//   return (0);
// }
// 
// void addToQueue(t_dongle *prev,
//                 t_dongle *next,
//                 int coder_id,
//                 long long deadline)
// {
//   if (isInQueue(prev, next, coder_id) 
//     || prev->count >= prev->cap 
//     || next->count >= next->cap)
//     return ;
//   prev->node[prev->count].dev_id = coder_id;
// 	prev->node[prev->count].arrival = get_time();
// 	prev->node[prev->count].deadline = deadline;
// 	prev->count++;
// 	next->node[next->count].dev_id = coder_id;
// 	next->node[next->count].arrival = get_time();
// 	next->node[next->count].deadline = deadline;
// 	next->count++;
// }
// 
// void	DelFromQueue(t_dongle *prev, t_dongle *next, int coder_id)
// {
// 	int	i;
// 
// 	i = 0;
// 	while (i < prev->count)
// 	{
// 		if (prev->node[i].dev_id == coder_id)
// 		{
// 			prev->node[i] = prev->node[prev->count - 1];
// 			prev->count--;
// 			return ;
// 		}
// 		if (next->node[i].dev_id == coder_id)
// 		{
// 			next->node[i] = next->node[next->count - 1];
// 			next->count--;
// 			return ;
// 		}
// 		i++;
// 	}
// }
// 
// int	isTop(t_dongle *prev, t_dongle *next, int coder_id, int scheduler)
// {
// 	int	best;
// 	int	i;
// 
// 	best = 0;
// 	i = 1;
// 	if (prev->count == 0)
// 		return (1);
// 	while (i < prev->count)
// 	{
// 		if (scheduler == 0
// 			&& prev->node[i].arrival < prev->node[best].arrival)
// 			best = i;
// 		else if (scheduler == 1
// 			&& (prev->node[i].deadline < prev->node[best].deadline
// 				|| (prev->node[i].deadline == prev->node[best].deadline
// 					&& prev->node[i].arrival < prev->node[best].arrival)))
// 			best = i;
// 		i++;
// 	}
// 	return (prev->node[best].dev_id == coder_id);
// }
