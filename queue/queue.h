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

void add_queue(int **queue, int *current_size, int id_dev);
void print_queue(int *queue, int length);
void pop_queue(int **queue, int *length, int ind_pop);

#endif
