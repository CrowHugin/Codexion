/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:27:27 by bastien           #+#    #+#             */
/*   Updated: 2026/08/29 00:08:53 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "monitoring/monitoring.h"
#include "devs/dev.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int		*options;
	t_dev	*coders;

	options = malloc(sizeof(int) * argc);
	if (!options)
		return (1);
	parsing(argc, argv, options);

	coders = malloc(sizeof(t_dev) * options[0]);
	if (!coders)
		return (1);
	set_up_dev(coders, options[0]);
	monitoring(coders, options);
	free(options);
	free(coders);
}
