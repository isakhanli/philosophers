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

int	check_argv(int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
		}
	}
	return (1);
}

int save_args(t_all *all, int argc, char **argv)
{
	all->args->n_philos = ft_atoi(argv[1]);
	all->args->t_die = ft_atoi(argv[2]);
	all->args->t_eat = ft_atoi(argv[3]);
	all->args->t_sleep = ft_atoi(argv[4]);
	all->args->n_eat = -1;
	if (argc == 6)
	{
		all->args->n_eat = ft_atoi(argv[5]);
		all->n_all_eats = 0;
	}

	if (!check_args(all, argc) || !check_argv(argc, argv))
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
	all.status = 1;
	all.start_time = get_time();
	if (argc == 5 || argc == 6)
	{
		if (!(save_args(&all, argc, argv)))
			return (1);
		if (!start_threads(&all))
		{
			printf("Malloc error\n");
			return (1);
		}
	}
	else
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	return (0);
}