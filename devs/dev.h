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
