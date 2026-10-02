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
	int	nbCoders;
	int	timeToBurnout;
	int	timeToCompile;
	int	timeToDebug;
	int	timeToRefactor;
	int	nbOfCompilesRequired;
	int	dongleCooldown;
	char	*scheduler;
}	t_options;

int	parsing(int argc, char *argv[], t_options *opts);

#endif
