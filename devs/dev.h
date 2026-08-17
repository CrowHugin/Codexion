/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 17:28:30 by bastien           #+#    #+#             */
/*   Updated: 2026/08/17 22:47:13 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H
# define DEV_H

typedef struct s_developper
{
	int	nb;
	int	has_doggle;
}	t_dev;

extern const t_dev	g_dev;
#endif
