/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 18:17:46 by dchin             #+#    #+#             */
/*   Updated: 2021/08/26 18:17:51 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define DEAD 0
# define OK 1
# define MALLOC_ERROR 1
# define PTHREAD_ERROR 2
# define MUTEX_ERROR 3

typedef struct s_philo
{
	int					id;
	int					n_eat;
	long long			last_meal;
	pthread_t			pth;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	struct s_all		*all;
}				t_philo;

typedef struct s_args
{
	int					n_philos;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
}				t_args;

typedef struct s_all
{
	t_args				*args;
	t_philo				*philos;
	int					status;
	int					error;
	int					n_all_eats;
	long long			start_time;
	pthread_t			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mtx_message;
	pthread_mutex_t		mtx_status;
	pthread_mutex_t		mtx_eating;
}				t_all;

long long	get_time(void);
int			ft_atoi(char *str);
int			start_threads(t_all *all);
void		*monitor(void *arg);
void		handle_message(t_philo *philo, char *msg);
int			check_status(t_all *all);
void		handle_sleep(t_all *all, int ms_to_sleep);
void		handle_message(t_philo *philo, char *msg);
int			free_and_return(t_all *all, int error);
void		ft_clean(t_all *all);
void		handle_eating(t_philo *philo);
void		*control_philos(t_all *all);

#endif
