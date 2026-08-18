/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:41:25 by bastien           #+#    #+#             */
/*   Updated: 2026/08/18 17:44:23 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef struct s_errors
{
	char	*err_0;
	char	*err_1;
	char	*err_2;
	char	*err_3;
	char	*err_4;
}	t_errors;

extern const t_errors	g_err;

void	print_error(const char *error);
#endif
