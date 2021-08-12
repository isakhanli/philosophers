#include "../includes/philo.h"

int	check_args(t_all *all, int argc)
{
	if (all->args->n_philos <= 0 || all->args->t_die <= 0
		|| all->args->t_eat <= 0 || all->args->t_sleep <= 0)
		return (0);
	if (argc == 6 && all->args->n_eat <= 0)
		return (0);
	return (1);
}

int save_args(t_all *all, int argc, char **argv)
{
	all->args->n_philos = ft_atoi(argv[1]);
	all->args->t_die = ft_atoi(argv[2]);
	all->args->t_eat = ft_atoi(argv[3]);
	all->args->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->args->n_eat = ft_atoi(argv[5]);
	if (!check_args(all, argc))
	{
		printf("Invalid argument\n");
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_all all;
	t_args args;

	all.args = &args;
	if (argc == 5 || argc == 6)
	{
		if (!(save_args(&all, argc, argv)))
			return (1);
		start_threads(&all);
	}
	else
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	return (0);
}