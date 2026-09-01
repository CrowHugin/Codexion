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

typedef struct dongle {
	int	nb;
	int	is_used;
	int	cooldown;
}	t_dongle;

typedef struct s_developper
{
	pthread_t				thread;
	struct s_developper	*all_coders;
	t_dongle			dongle;
	int						*queue;
	int						*options;
	int						nb;
	int						next_dev;
	int						prev_dev;
	enum e_state			state;
}	t_dev;

void	print_devs_infos(t_dev *coders, int len);
void	set_up_dev(t_dev *coders, int *options, int *queue);
void	*dev_behaivor(void *arg);
void	take_dongle(t_dev *coders);
void	free_dongle(t_dev *dev);
int		is_dongle_free(t_dev *dev);
#endif
