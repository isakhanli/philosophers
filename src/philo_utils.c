#include "../includes/philo.h"

int check_status(t_all *all)
{
	pthread_mutex_lock(&all->mtx_status);
	if (all->status != 1)
	{
		pthread_mutex_unlock(&all->mtx_status);
		return (0);
	}
	pthread_mutex_unlock(&all->mtx_status);
	return (1);
}

void 	handle_sleep(t_all *all, int ms_to_sleep)
{
	long long start;

	start = get_time();
	while ((get_time() - start) < ms_to_sleep)
	{
		pthread_mutex_lock(&all->mtx_status);
		if (all->status != OK)
		{
			pthread_mutex_unlock(&all->mtx_status);
			return ;
		}
		pthread_mutex_unlock(&all->mtx_status);
		usleep(40);
	}
}

void 	handle_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->all->mtx_message);
	if (philo->all->status == OK)
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
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->all->mtx_eating);
	if (philo->all->args->n_eat != -1)
		philo->n_eat++;
	pthread_mutex_unlock(&philo->all->mtx_eating);
}
