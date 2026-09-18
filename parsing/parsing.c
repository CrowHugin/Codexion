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

int	parsing_helper(char *str, int *options, int *j)
{
	if (str[0] == '-' && is_int(str + 1))
	{
		printf("ERROR:\nNumbers cannot be negative\n");
		return (1);
	}
	else if (!is_int(str))
	{
		printf("ERROR:\nYou do not have 7 positive ints\n");
		return (1);
	}
	else if (str[0] != '-' && is_int(str))
	{
		options[*j] = atoi(str);
		(*j)++;
	}
	return (0);
}

int	parsing(int argc, char *argv[], int *options)
{
	char	*last_arg;
	int		j;
	int		i;

	j = 0;
	i = 1;
	last_arg = argv[argc - 1];
	if (argc != 9)
	{
		printf("EEROR\nYou do not have 8 args\n");
		return (1);
	}
	if (strcmp(last_arg, "fifo") != 0 && strcmp(last_arg, "edf") != 0)
	{
		printf("ERROR:\nLast arg is not \"fifo\" or \"edf\"");
		return (1);
	}
	while (i != argc - 1)
	{
		if (parsing_helper(argv[i], options, &j))
			return (1);
		i++;
	}
	options[7] = 0;
	if (strcmp(last_arg, "edf") == 0)
		options[7] = 1;
	return (0);
}
