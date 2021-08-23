#include "../includes/philo.h"

void	*handle_philosoper(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->all->args->n_eat != -1
			&& philo->n_eat >= philo->all->args->n_eat)
			return (NULL);
		if (!check_status(philo))
			return (NULL);
		handle_eating(philo);
		if (!check_status(philo))
			return (NULL);
		handle_message(philo, "is sleeping");
		handle_sleep(philo->all, philo->all->args->t_sleep);
		if (!check_status(philo))
			return (NULL);
		handle_message(philo, "is thinking");
	}
}

void 	init_philos(t_all *all, int *i)
{
	all->philos[*i].all = all;
	all->philos[*i].id = *i;
	all->philos[*i].n_eat = 0;
	all->philos[*i].l_fork = &all->forks[*i];
	if (*i == all->args->n_philos - 1)
	{
		all->philos[*i].r_fork = &all->forks[0];
	}
	else
		all->philos[*i].r_fork = &all->forks[*i + 1];
	all->philos[*i].last_meal = all->start_time;
	pthread_create(&all->philos[*i].pth, NULL, handle_philosoper,
				   &all->philos[*i]);
	(*i) += 2;
}

int		create_philos(t_all *all)
{
	int i;

	i = 0;
	while (i < all->args->n_philos)
		init_philos(all, &i);
	handle_sleep(all, 10);
	i = 1;
	while (i < all->args->n_philos)
		init_philos(all, &i);
	return (1);
}

void init_mutexes(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->args->n_philos)
		pthread_mutex_init(&all->forks[i], NULL);
	pthread_mutex_init(&all->mtx_message, NULL);
	pthread_mutex_init(&all->mtx_status, NULL);
	pthread_mutex_init(&all->mtx_n_all_eats, NULL);
}

int		start_threads(t_all *all)
{
	all->status = 1;
	all->start_time = get_time();
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->args->n_philos);
	if (!all->philos)
		return free_and_return(all);
	all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* all->args->n_philos);
	if (!all->forks)
		return free_and_return(all);
	init_mutexes(all);
	create_philos(all);
	pthread_create(&all->monitor, NULL, monitor, all);
	pthread_join(all->monitor, NULL);
	destroy_all(all);
	return (1);
}
