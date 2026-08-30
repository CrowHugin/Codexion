/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <email>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:29:56 by bastien           #+#    #+#             */
/*   Updated: 2026/08/30 10:14:17 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H
# define DEV_H

# include <pthread.h>

enum e_state
{
	STATE_COMPILE,
	STATE_DEBUG,
	STATE_REFACTOR
};

typedef struct s_developper
{
	pthread_t				thread;
	struct s_developper	*all_coders;
	int						*queue;
	int						has_doggle;
	int						nb;
	int						next_dev;
	int						prev_dev;
	enum e_state			state;
}	t_dev;

void	print_devs_infos(t_dev *coders, int len);
void	set_up_dev(t_dev *coders, int len, int *queue);
void	*dev_behaivor(void *arg);
void	take_dongle(t_dev *coders);
#endif
