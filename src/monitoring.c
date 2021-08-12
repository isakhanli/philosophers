#include "../includes/philo.h"

int is_dead(t_all *all, int i)
{
	if (get_time() > all->philos[i].max_eating)
	{
		pthread_mutex_lock(&all->mtx_message);
		printf("%d is dead\n", all->philos[i].id +1);
		pthread_mutex_unlock(&all->mtx_message);
		return (1);
	}
	return (0);
}


void *monitor(void *arg)
{
	t_all	*all;
	int i;

	all = (t_all *)arg;
	while(1)
	{
		i = -1;
		while (++i < all->args->n_philos)
		{
			if (is_dead(all, i))
				return NULL;
		}
	}
}
