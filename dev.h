/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 17:28:30 by bastien           #+#    #+#             */
/*   Updated: 2026/08/17 17:29:50 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H
# define DEV_H

typedef struct s_developper
{
	
	char	*err_0;
	char	*err_1;
	char	*err_2;
}	t_errors;

extern const t_errors	g_err;
#endif
