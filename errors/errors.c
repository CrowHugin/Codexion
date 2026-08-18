/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz </var/spool/mail/bkuntz>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 16:14:04 by bkuntz            #+#    #+#             */
/*   Updated: 2026/08/18 16:15:08 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

const t_errors	g_err = {
	.err_0 = "ERROR:\nNumbers cannot be negatives\n",
	.err_1 = "ERROR:\nNot all args are ints\n",
	.err_2 = "ERROR:\nYou do not have 8 positive ints\n",
	.err_3 = "ERROR:\nLast arg is not \"fifo\" or \"edf\""
};

void	print_error(const char *error)
{
	printf("%s\n", error);
	exit(1);
}
