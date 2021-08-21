#include "../includes/philo.h"

int check_is_dead(t_all *all, int i)
{
	if (get_time() > all->philos[i].last_meal + all->args->t_die)
	{
		pthread_mutex_lock(&all->mtx_message);
		pthread_mutex_lock(&all->mtx_alive);
		all->alive = 0;
		pthread_mutex_unlock(&all->mtx_alive);
		printf("%lld %d %s\n", get_time() - all->start_time,
	   	i + 1, "is dead");
		pthread_mutex_unlock(&all->mtx_message);
		return (0);
	}
	return (1);
}

int check_eat_number(t_all *all)
{
	if (all->n_all_eats / all->args->n_philos >= all->args->n_eat
			&& all->args->n_eat != -1)
	{
		pthread_mutex_lock(&all->mtx_message);
		pthread_mutex_lock(&all->mtx_alive);
		all->alive = 0;
		pthread_mutex_unlock(&all->mtx_alive);
		pthread_mutex_unlock(&all->mtx_message);
		return 0;
	}
	return (1);
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
			if (!check_is_dead(all, i) || !check_eat_number(all))
				return NULL;
		}
	}
}
