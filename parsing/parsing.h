/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:48:00 by bastien           #+#    #+#             */
/*   Updated: 2026/08/17 11:48:01 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_options
{
	int	nb_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	nb_of_compiles_required;
	int	dongle_cooldown;
	char	*scheduler;
}	t_options;

int	parsing(int argc, char *argv[], t_options *opts);

#endif
