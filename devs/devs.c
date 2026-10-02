/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuntz <bkuntz@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:50:27 by bkuntz            #+#    #+#             */
/*   Updated: 2026/09/18 16:50:29 by bkuntz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dev.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void	set_up_dev(t_options *options,
								t_dev *coders,
								t_node **queue,
								atomic_int	*ptr_running,
								pthread_mutex_t *thread_lock)
{
	int		i;

	i = 0;
	while (i < options->nbCoders)
	{
		coders[i].nb = i + 1;
		coders[i].state = 0;
		coders[i].all_coders = coders;
		coders[i].queue = queue;
		coders[i].next_dev = (i + 1) % options->nbCoders;
		coders[i].prev_dev = (i + options->nbCoders - 1) % options->nbCoders;
		coders[i].options = options;
		coders[i].keep_running = ptr_running;
		coders[i].dongle.nb = i + 1;
		coders[i].dongle.is_used = false;
		coders[i].dongle.cooldown = options->dongleCooldown;
		coders[i].thread_lock = thread_lock;
		coders[i].dongle.available_at = 0;
		coders[i].dongle.is_used = false;
		pthread_mutex_init(&coders[i].dongle.mutex, NULL);
		pthread_cond_init(&coders[i].dongle.cond, NULL);
		i++;
	}
}

void	change_state(t_dev *dev, long long start_time, int *ind)
{
	t_node	*tmp;
  long long target_ms;
  struct timespec ts;

	tmp = *(dev->queue);
  while (tmp != NULL && tmp->dev_id != dev->nb && tmp->dev_id != -dev->nb)
    tmp = tmp->next;
  if (!tmp)
    return ;
	if (dev->state == 0)
	{
		if (take_dongle(dev, start_time) == 1)
		{
      pthread_mutex_lock(dev->thread_lock);
      if (atomic_load(dev->keep_running) == 1)
      {
        target_ms = get_time() + 1;
        ts.tv_sec = target_ms / 1000;
        ts.tv_nsec = (target_ms % 1000) * 1000000LL;
        pthread_cond_timedwait(&tmp->cond, dev->thread_lock, &ts);
      }
      pthread_mutex_unlock(dev->thread_lock);
		}
		else 
		{
			pthread_mutex_lock(dev->thread_lock);
			dev->state = 1;
			dev->last_compile_time = get_time();
			enable_wait(tmp);
      update_node_deadline(dev->queue, dev->nb, dev->last_compile_time + 
          dev->options->timeToBurnout);
      pthread_mutex_unlock(dev->thread_lock);
			printf("%llu %d is compiling\n", get_time() - start_time, dev->nb);
			usleep(dev->options->timeToCompile);
			release_dongles(dev);
			(*ind)++;
		}
	}
	else if (dev->state == 1)
	{
    pthread_mutex_lock(dev->thread_lock);
		dev->state = 2;
		printf("%llu %d is debugging\n", get_time() - start_time, dev->nb);
    pthread_mutex_unlock(dev->thread_lock);
		usleep(dev->options->timeToDebug);
	}
	else if (dev->state == 2)
	{
    pthread_mutex_lock(dev->thread_lock);
		dev->state = 0;
		printf("%llu %d is refactoring\n", get_time() - start_time, dev->nb);
		usleep(dev->options->timeToRefactor);
    stop_wait(tmp);
    move_to_last(dev->queue, tmp);
    pthread_mutex_unlock(dev->thread_lock);
	}
}

void	*dev_behaivor(void *arg)
{
	long long	start_time;
	t_dev		*coders;
	int			i;

	start_time = get_time();
	coders = (t_dev *)arg;
	i = 0;
  pthread_mutex_lock(coders->thread_lock);
	coders->last_compile_time = start_time;
  pthread_mutex_unlock(coders->thread_lock);
	while (i < coders->options->nbOfCompilesRequired
		&& atomic_load(coders->keep_running) == true)
		change_state(coders, start_time, &i);
  pthread_mutex_lock(coders->thread_lock);
	if (atomic_load(coders->keep_running) == true)
		coders->state = STATE_FINNISH;
  pthread_mutex_unlock(coders->thread_lock);
	return (NULL);
}
