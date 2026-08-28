#include "../devs/dev.h"
#include "../errors/errors.h"
#include "../states/states.h"
#include <stdio.h>
#include <stdlib.h>

void *print_hello(void *arg)
{
	(void)arg;
	printf("HELLO\n");
	return NULL;
}

int create_thread(t_dev *coders, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		int res;

		res = pthread_create(&coders[i].thread, NULL, change_state, (void *)&coders[i]);
		if (res)
			print_error(g_err.err_4);
		i++;
	}
	i = 0;
	while (i < len)
	{
			pthread_join(coders[i].thread, NULL);
			i++;
	}
	return (0);
}

int monitoring(t_dev *coders, int *options)
{
	create_thread(coders, options[0]);
	return(0);
}
