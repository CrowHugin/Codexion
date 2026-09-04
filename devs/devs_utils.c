/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:34:21 by bastien           #+#    #+#             */
/*   Updated: 2026/08/30 00:34:36 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "dev.h"

void	print_base_infos(t_dev coders, int j)
{
	printf("Coder %d:\n", j + 1);
	printf("	numbers: %d\n", coders.nb);
	printf("	state: %d\n", coders.state);
	printf("	running: %d\n", *coders.keep_running);
}

void	print_devs_infos(t_dev *coders, int len)
{
	int	j;

	j = 0;
	printf("nb coders: %d\n", len);
	print_base_infos(coders[j], j);
	printf("	has_doggle right: %d\n", coders[j + 1].dongle.is_used);
	printf("	has_doggle left: %d\n", coders[len - 1].dongle.is_used);
	j++;
	while (j < len - 1)
	{
		print_base_infos(coders[j], j);
		printf("	has_doggle right: %d\n", coders[j + 1].dongle.is_used);
		printf("	has_doggle left: %d\n", coders[j - 1].dongle.is_used);
		j++;
	}
	print_base_infos(coders[j], j);
	printf("	has_doggle right: %d\n", coders[0].dongle.is_used);
	printf("	has_doggle left: %d\n", coders[j].dongle.is_used);
}

long long get_time(void)
{
	struct timeval tv;
	long long milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (milliseconds);
}
