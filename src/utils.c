#include "../includes/philo.h"

static int		ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' || c == '\f' ||
	c == '\r' || c == ' ')
		return (1);
	return (0);
}

int				ft_atoi(char *str)
{
	long	result;
	int		i;
	int		is_neg;

	i = 0;
	result = 0;
	is_neg = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg = is_neg * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result += str[i] - 48;
		i++;
	}
	return ((is_neg * result));
}

long long get_time(void)
{
	struct timeval	cur_time;

	if (gettimeofday(&cur_time, NULL) == -1)
		return -1;
	return ((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000));
}