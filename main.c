/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:27:27 by bastien           #+#    #+#             */
/*   Updated: 2026/08/17 11:47:53 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "parsing/parsing.h"

const t_errors	g_err = {
	.err_0 = "ERROR:\nNumbers cannot be negatives\n",
	.err_1 = "ERROR:\nNot all args are ints\n",
	.err_2 = "ERROR:\nYou do not have 8 positive ints\n",
};

int	main(int argc, char *argv[])
{
	int	*options;
	options = malloc(sizeof(int) * argc);
	if (options == NULL)
		return (1);
	parsing(argc, argv, options);
	for (int i = 0; i<get_len(options); i++)
		printf("%d", options[i]);
}
