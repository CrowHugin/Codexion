/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 17:28:30 by bastien           #+#    #+#             */
/*   Updated: 2026/08/29 00:01:35 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H
# define DEV_H

# include <pthread.h>
typedef struct s_developper
{
	int			nb;
	int			has_doggle;
	enum e_state {
    STATE_COMPILE,
    STATE_DEBUG,
    STATE_REFACTOR
	}state;
	pthread_t thread;
}	t_dev;

void	print_devs_infos(t_dev *coders, int len);
void	set_up_dev(t_dev *coders, int len);
#endif
