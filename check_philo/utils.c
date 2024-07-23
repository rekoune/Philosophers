#include "philo.h"

void	ft_sleep(long time)
{
	size_t current_time;

	current_time = get_time();
	while((current_time + time) > get_time())
		usleep(100);
}

int	error(char *str)
{
	printf("%s", str);
	return(0);
}

size_t	get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	ft_atoi(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (!str)
	{
		printf("Error : Invalid arguments\n");
		return(-1);
	}
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			printf("Error : Invalid arguments\n");
			return(-1);
		}
		nb = nb * 10;
		nb = nb + (str[i] - 48);
		i++;
	}
	return(nb);
}
