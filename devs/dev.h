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
# include <stdbool.h>
# include <stdatomic.h>

enum e_state
{
	STATE_COMPILE,
	STATE_DEBUG,
	STATE_REFACTOR,
	STATE_BURNOUT
};

typedef struct dongle
{
	int		nb;
	int		cooldown;
	bool	is_used;
	long long available_at;
	pthread_mutex_t mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_developper
{
	pthread_t						thread;
	struct s_developper				*all_coders;
	t_dongle						dongle;
	long long						last_compile_time;
	pthread_mutex_t					*thread_lock;
	int								*queue;
	int								*options;
	atomic_int								*keep_running;
	int								nb;
	int								next_dev;
	int								prev_dev;
	enum e_state					state;
}	t_dev;

void	print_devs_infos(t_dev *coders, int len);
void	set_up_dev(t_dev *coders,
			int *options,
			int *queue,
			atomic_int *ptr_running,
			pthread_mutex_t *thread_lock);
void	*dev_behaivor(void *arg);
void	take_dongle(t_dev *coders, long long time);
void	free_dongle(t_dev *dev);
int		is_dongle_free(t_dev *dev);
void lock_two_dongles(t_dongle *a, t_dongle *b);
void unlock_two_dongles(t_dongle *a, t_dongle *b);
long long	get_time(void);
#endif
