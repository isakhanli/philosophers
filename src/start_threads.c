#include "../includes/philo.h"

void 	handle_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->all->mtx_message);
	if (!philo->all->has_dead)
		printf("%lld %d %s\n", get_time() - philo->all->time,
			   philo->id + 1, msg);
	pthread_mutex_unlock(&philo->all->mtx_message);
}

void	handle_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	handle_message(philo, "has taken fork");
	pthread_mutex_lock(philo->r_fork);
	handle_message(philo, "has taken fork");
	pthread_mutex_lock(&philo->mtx_eating);
	handle_message(philo, "is eating");
	philo->last_eating = get_time();
	philo->max_eating = get_time()	 + philo->all->args->t_die;
	pthread_mutex_unlock(&philo->mtx_eating);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*handle_philosoper(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		handle_eating(philo);
		handle_message(philo, "is sleeping");
		usleep(1000);
		handle_message(philo, "is thinking");
	}
}

void 	set_forks(t_all *all, int i)
{
	all->philos[i].r_fork = &all->forks[i];
	if (i == 0)
	{
		all->philos[i].l_fork = &all->forks[all->args->n_philos - 1];
	}
	else
		all->philos[i].l_fork = &all->forks[i - 1];
}

int		create_philos(t_all *all)
{
	int i;
	i = -1;
	while (++i < all->args->n_philos)
	{
		all->philos[i].all = all;
		all->philos[i].id = i;
		set_forks(all, i);
		pthread_mutex_init(&all->philos->mtx_eating, NULL);
		pthread_create(&all->philos[i].pth, NULL, handle_philosoper,
					   &all->philos[i]);
		usleep(100);
		i++;
	}
	return (1);
}

int		start_threads(t_all *all)
{
	int i;

	i = -1;
	all->has_dead = FALSE;
	all->time = get_time();
	if (all->time == -1)
		return (0);
	all->philos = malloc(sizeof(t_philo) * all->args->n_philos);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->args->n_philos);
	while (++i < all->args->n_philos)
		pthread_mutex_init(&all->forks[i], NULL);
	pthread_mutex_init(&all->mtx_message, NULL);
	create_philos(all);
	pthread_create(&all->monitor, NULL, monitor, all);
	pthread_join(all->monitor, NULL);



	return (1);
}
