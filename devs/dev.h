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
# include "../parsing/parsing.h"
# include "../queue/queue.h"

typedef struct s_node t_node;

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
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	long long		available_at;
	int				nb;
	int				cooldown;
	bool			is_used;
}	t_dongle;

typedef struct s_developper
{
	long long						last_compile_time;
	t_options						*options;
	struct s_developper				*all_coders;
	pthread_mutex_t					*thread_lock;
	atomic_int						*keep_running;
	pthread_t						thread;
	t_dongle						dongle;
	t_node							**queue;
	int								nb;
	int								next_dev;
	int								prev_dev;
	enum e_state					state;
}	t_dev;

long long	get_time(void);
void		print_devs_infos(t_dev *coders, int len);
void	set_up_dev(t_options *options,
								t_dev *coders,
								t_node **queue,
								atomic_int	*ptr_running,
								pthread_mutex_t *thread_lock);
void		*dev_behaivor(void *arg);
void		acquire_dongle(t_dev *dev, t_dongle *d,
				int coder_id, long long deadline,
				int sched, long long start_time);
void	release_dongles(t_dev *coder);
int	take_dongle(t_dev *coder, long long start);
void		check_burnout(t_dev *dev, long long start_time);
#endif
