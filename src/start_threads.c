/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 18:18:04 by dchin             #+#    #+#             */
/*   Updated: 2021/08/26 18:18:05 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*handle_philosoper(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->all->args->n_eat != -1
			&& philo->n_eat >= philo->all->args->n_eat)
			return (NULL);
		if (!check_status(philo->all))
			return (NULL);
		handle_eating(philo);
		if (!check_status(philo->all))
			return (NULL);
		handle_message(philo, "is sleeping");
		handle_sleep(philo->all, philo->all->args->t_sleep);
		if (!check_status(philo->all))
			return (NULL);
		handle_message(philo, "is thinking");
	}
}

int	init_philos(t_all *all, int *i)
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
	if (pthread_create(&all->philos[*i].pth, NULL, handle_philosoper,
			&all->philos[*i]))
		return (0);
	(*i) += 2;
	return (1);
}

int	create_philos(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->args->n_philos)
	{
		if (!(init_philos(all, &i)))
			return (0);
	}
	handle_sleep(all, 10);
	i = 1;
	while (i < all->args->n_philos)
	{
		if (!(init_philos(all, &i)))
			return (0);
	}
	return (1);
}

int	init_mutexes(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->args->n_philos)
	{
		if (pthread_mutex_init(&all->forks[i], NULL))
			return (0);
	}
	if (pthread_mutex_init(&all->mtx_message, NULL))
		return (0);
	if (pthread_mutex_init(&all->mtx_status, NULL))
		return (0);
	if (pthread_mutex_init(&all->mtx_eating, NULL))
		return (0);
	return (1);
}

int	start_threads(t_all *all)
{
	int	i;

	all->status = 1;
	all->start_time = get_time();
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->args->n_philos);
	if (!all->philos)
		return (free_and_return(all, MALLOC_ERROR));
	all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* all->args->n_philos);
	if (!all->forks)
		return (free_and_return(all, MALLOC_ERROR));
	if (!init_mutexes(all))
		return (free_and_return(all, MUTEX_ERROR));
	if (!(create_philos(all)))
		return (free_and_return(all, PTHREAD_ERROR));
	control_philos(all);
	i = -1;
	while (++i < all->args->n_philos)
	{
		if (all->args->n_philos == 1)
			pthread_mutex_unlock(all->philos[0].r_fork);
		pthread_join(all->philos[i].pth, NULL);
	}
	ft_clean(all);
	return (1);
}
