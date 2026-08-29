/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 23:24:43 by bastien           #+#    #+#             */
/*   Updated: 2026/08/29 23:25:14 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../errors/errors.h"
#include <stdlib.h>
#include <stdio.h>

void add_queue(int **queue, int *current_size, int id_dev)
{
	int new_size;
	int *new_queue;
	int i;

	i = 0;
	new_size = *current_size + 1;
	new_queue = malloc(new_size * sizeof(int));
	if (new_queue == NULL)
		print_error(g_err.err_5);

	if (*queue != NULL)
	{
		while (i < *current_size)
		{
			new_queue[i] = (*queue)[i];
			i++;
		}
		free(*queue);
	}
	new_queue[*current_size] = id_dev;
	*queue = new_queue;
	*current_size = new_size;
}

void pop_queue(int **queue, int *length, int ind_pop)
{
	int i;
	int j;
	int *new_queue;
	int new_size;

	i = 0;
	j = 0;
	new_size = *length - 1;
	new_queue = malloc(new_size * sizeof(int));
	while (i < *length)
	{
		if (i != ind_pop)
		{
			new_queue[j] = (*queue)[i];
			j++;
		}
		i++;
	}
	free(*queue);
	*queue = new_queue;
	*length = new_size;
}

void print_queue(int *queue, int length)
{
	int i;

	i = 0;
	while (i < length - 1)
	{
 		printf("%d, ", queue[i]);
		i++;
	}
	printf("%d\n", queue[i]);
}
