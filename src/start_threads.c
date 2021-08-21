#include "../includes/philo.h"

int check_if_alive(t_all *all)
{
	pthread_mutex_lock(&all->mtx_alive);
	if (!all->alive)
	{
		pthread_mutex_unlock(&all->mtx_alive);
		return (0);
	}
	pthread_mutex_unlock(&all->mtx_alive);
	return (1);
}

void 	handle_sleep(t_all *all, int ms_to_sleep)
{
	long long start;

	start = get_time();
	while ((get_time() - start) < ms_to_sleep)
	{
		pthread_mutex_lock(&all->mtx_alive);
		if (!all->alive)
		{
			pthread_mutex_unlock(&all->mtx_alive);
			return ;
		}
		pthread_mutex_unlock(&all->mtx_alive);
		usleep(100);
	}
}

void 	handle_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->all->mtx_message);
	if (philo->all->alive)
		printf("%lld %d %s\n", get_time() - philo->all->start_time,
			   philo->id + 1, msg);
	pthread_mutex_unlock(&philo->all->mtx_message);
}

void	handle_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	handle_message(philo, "has taken fork");
	pthread_mutex_lock(philo->r_fork);
	handle_message(philo, "has taken fork");
	handle_message(philo, "is eating");
	philo->last_meal = get_time();
	handle_sleep(philo->all, philo->all->args->t_eat);
	pthread_mutex_lock(&philo->all->mtx_n_all_eats);
	if (philo->all->args->n_eat != -1)
		philo->all->n_all_eats++;
	pthread_mutex_unlock(&philo->all->mtx_n_all_eats);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);


}

void	*handle_philosoper(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->all->n_all_eats / philo->all->args->n_philos >=
			philo->all->args->n_eat && philo->all->args->n_eat != -1)
			return NULL;
		if (!check_if_alive(philo->all))
			return (NULL);
		handle_eating(philo);
		if (!check_if_alive(philo->all))
			return (NULL);
		handle_message(philo, "is sleeping");
		handle_sleep(philo->all, philo->all->args->t_sleep);
		if (!check_if_alive(philo->all))
			return (NULL);
		handle_message(philo, "is thinking");
	}
}

void 	set_forks(t_all *all, int i)
{
	all->philos[i].l_fork = &all->forks[i];
	if (i == all->args->n_philos - 1)
	{
		all->philos[i].r_fork = &all->forks[0];
	}
	else
		all->philos[i].r_fork = &all->forks[i + 1];
}

void 	init_philos(t_all *all, int *i)
{
	all->philos[*i].all = all;
	all->philos[*i].id = *i;
	set_forks(all, *i);
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

void 	destroy_all(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->args->n_philos)
		pthread_detach(all->philos[i].pth);
	i = -1;
	while (++i < all->args->n_philos)
		pthread_mutex_destroy(&all->forks[i]);
	free(all->philos);
	free(all->forks);
}

int free_and_return(t_all *all)
{
	if (all->philos)
		free(all->philos);
	if (all->forks)
		free(all->forks);
	all->error = MALLOC_ERROR;
	return (0);
}

int		start_threads(t_all *all)
{
	int i;

	i = -1;
	all->alive = 1;
	all->start_time = get_time();
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->args->n_philos);
	if (!all->philos)
		return free_and_return(all);
	all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* all->args->n_philos);
	if (!all->forks)
		return free_and_return(all);
	while (++i < all->args->n_philos)
		pthread_mutex_init(&all->forks[i], NULL);
	pthread_mutex_init(&all->mtx_message, NULL);
	pthread_mutex_init(&all->mtx_alive, NULL);
	pthread_mutex_init(&all->mtx_n_all_eats, NULL);
	create_philos(all);
	pthread_create(&all->monitor, NULL, monitor, all);
	pthread_join(all->monitor, NULL);
	destroy_all(all);
	return (1);
}
