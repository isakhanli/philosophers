/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 18:17:53 by dchin             #+#    #+#             */
/*   Updated: 2021/08/26 18:17:55 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo(t_all *all, int i, int *is_full)
{
	if (get_time() > all->philos[i].last_meal + all->args->t_die)
	{
		pthread_mutex_lock(&all->mtx_message);
		pthread_mutex_lock(&all->mtx_status);
		all->status = 0;
		pthread_mutex_unlock(&all->mtx_status);
		printf("%lld %d %s\n", get_time() - all->start_time,
			   i + 1, "is dead");
		pthread_mutex_unlock(&all->mtx_message);
		return (0);
	}
	pthread_mutex_lock(&all->mtx_eating);
	if (all->args->n_eat != -1 && all->philos[i].n_eat >= all->args->n_eat)
		(*is_full)++;
	pthread_mutex_unlock(&all->mtx_eating);
	return (1);
}

void	*control_philos(t_all *all)
{
	int	i;
	int	is_full;

	while (1)
	{
		i = -1;
		is_full = 0;
		while (++i < all->args->n_philos)
		{
			if (!check_philo(all, i, &is_full))
				return (NULL);
		}
		if (all->args->n_eat != -1 && is_full == all->args->n_philos)
		{
			return (NULL);
		}
	}
}
