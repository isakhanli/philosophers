#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

typedef struct 	s_philo
{
	int 				id;
	pthread_t			pth;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		mtx_eating;
	long long 			last_eating;
	long long 			max_eating;
	struct s_all 		*all;

}				t_philo;

typedef struct s_args
{
	int 		n_philos;
	int 		t_die;
	int 		t_eat;
	int 		t_sleep;
	int 		n_eat;

}				t_args;

typedef struct	s_all
{
	t_args			*args;
	t_philo 		*philos;
	int 			has_dead;
	long long 		time;
	pthread_t 		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mtx_message;
	pthread_mutex_t	mtx_has_dead;

}				t_all;

int		ft_atoi(char *str);
int		start_threads(t_all *all);
long long	get_time();
void *monitor(void *arg);

#endif
