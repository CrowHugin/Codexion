/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:27:19 by bastien           #+#    #+#             */
/*   Updated: 2026/08/17 11:47:39 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../errors.h"

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

void	parsing_helper(char *str, int *options, int *j)
{
	if (str[0] == '-' && is_int(str + 1))
	{
		printf("%s\n", g_err.err_0);
		exit(1);
	}
	else if (!is_int(str))
	{
		printf("%s\n", g_err.err_1);
		exit(1);
	}
	else if (str[0] != '-' && is_int(str))
	{
		options[*j] = atoi(str);
		(*j)++;
	}
}

int	*parsing(int argc, char *argv[], int *options)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	while (i != argc)
	{
		parsing_helper(argv[i], options, &j);
		i++;
	}
	if (get_len(options) != 8)
	{
		printf("%s", g_err.err_2);
		exit(1);
	}
	return (0);
}
