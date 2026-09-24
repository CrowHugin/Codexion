/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:51:06 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:51:08 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

int	get_len(int *ptr_tab)
{
	int	i;

	i = 0;
	while (ptr_tab[i] != '\0')
		i++;
	return (i);
}

int	is_int(char	*src)
{
	int	len;
	int	j;

	len = strlen(src);
	j = 0;
	while (j < len)
	{
		if ((src[0] != '+' && src[0] != '-') && (src[j] < 48 || src[j] > 57))
			return (0);
		j++;
	}
	return (1);
}

int	parsing_errors(char *args[], int nb_args)
{
	int	i;

	i = 1;
	if (nb_args != 9)
	{
		printf("ERROR\nYou do not have 8 args\n");
		return (1);
	}
	while (i != nb_args - 1)
	{
		if (args[i][0] == '-' && is_int(args[i] + 1))
		{
			printf("ERROR:\nNumbers cannot be negative\n");
			return (1);
		}
		else if (!is_int(args[i]))
		{
			printf("ERROR:\nYou do not have 7 positive ints\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing(int argc, char *argv[], t_options *opts)
{
	int	res;

	res = 0;
	if (strcmp(argv[argc - 1], "fifo") != 0
		&& strcmp(argv[argc - 1], "edf") != 0)
	{
		printf("ERROR:\nLast arg is not \"fifo\" or \"edf\"");
		return (1);
	}
	res = parsing_errors(argv, argc);
	if (res == 1)
		return (1);
	opts->nbCoders = atoi(argv[1]);
	opts->timeToBurnout = atoi(argv[2]);
	opts->timeToCompile = atoi(argv[3]);
	opts->timeToDebug = atoi(argv[4]);
	opts->timeToRefactor = atoi(argv[5]);
	opts->nbOfCompilesRequired = atoi(argv[6]);
	opts->dongleCooldown = atoi(argv[7]);
	opts->scheduler = "fifo";
	if (strcmp(argv[argc - 1], "edf") == 0)
		opts->scheduler = "edf";
	return (0);
}
