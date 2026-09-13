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

typedef struct s_request
{
	int				dev_id;
	long long	arrival;
	long long	deadline;
}	t_request;

enum e_state
{
	STATE_COMPILE,
	STATE_DEBUG,
	STATE_REFACTOR,
	STATE_BURNOUT,
	STATE_FINNISH
};

typedef struct dongle
{
	int		nb;
	int		cooldown;
	bool	is_used;
	long long available_at;
	pthread_mutex_t mutex;
	pthread_cond_t	cond;
	t_request	*waiters;
	int				count;
	int				cap;
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
long long	get_time(void);
void acquire_dongle(t_dev *dev, t_dongle *d, 
										int coder_id, long long deadline,
										int sched, long long start_time);
void release_dongle(t_dongle *d, int cooldown);
void	take_dongle(t_dev *coders, long long time);
void	check_burnout(t_dev *dev, long long start_time);
#endif
