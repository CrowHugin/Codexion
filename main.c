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

#include <stdlib.h>
#include "parsing/parsing.h"
#include "devs/dev_share.h"

int	main(int argc, char *argv[])
{
	int		*options;

	options = malloc(sizeof(int) * argc);
	if (!options)
		return (1);
	parsing(argc, argv, options);
	// set_up_dev(options);
	free(options);
}
