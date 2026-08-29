#include "../devs/dev.h"
#include <stdio.h>

void *change_state(void *arg)
{
	t_dev *dev = (t_dev *)arg;
	char *state_name[] = {"STATE_COMPILE", "STATE_DEBUG", "STATE_REFACTOR"};
	if (dev->state == 0)
	{
		dev->state = 1;
		printf("dev nb°%d -> %s\n", dev->nb, state_name[dev->state]);
	}
	else if (dev->state == 1)
	{
		dev->state = 2;
		printf("dev nb°%d -> %s\n", dev->nb, state_name[dev->state]);
	}
	else if (dev->state == 2)
	{
		dev->state = 0;
		printf("dev nb°%d -> %s\n", dev->nb, state_name[dev->state]);
	}
	return NULL;
}
