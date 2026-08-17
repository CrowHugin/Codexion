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

# include "../errors.h"

int	get_len(int	*ptr_tab);
int	is_int(char	*src, t_errors ERR);
int	*parsing(int	argc, char	*argv[], int	*options);

#endif
