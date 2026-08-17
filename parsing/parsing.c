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

int	is_int(char	*src, t_errors Err)
{
	int	len;
	int	j;

	len = strlen(src);
	j = 0;
	while (j < len)
	{
		if (src[0] == '-')
		{
			printf("%s", Err.err_0);
			exit(1);
		}
		else if (src[j] < 48 || src[j] > 57)
		{
			printf("%s", Err.err_1);
			exit(1);
		}
		j++;
	}
	return (0);
}

int	*parsing(int	argc, char	*argv[], int	*options)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	while (i != argc)
	{
		if (is_int(argv[i], g_err) == 0)
		{
			options[j] = atoi(argv[i]);
			j++;
			i++;
		}
		else
			exit(1);
	}
	if (get_len(options) != 8)
	{
		printf("%s", g_err.err_2);
		exit(1);
	}
	return (0);
}
