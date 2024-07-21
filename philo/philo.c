#include "philo.h"

int	get_info(char *str)
{
	int nb;
	int i;

	i = 0;
	nb = 0;
	if (str[0] == '-')
		error("error: negatif argument\n");
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			error("error: argument is not a number \n");
		nb = nb * 10;
		nb = nb + (str[i] - 48);
		i++;
	}
	return(nb);
}

size_t get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void check_time(t_philo *philo)
{
	int i;
	size_t last_eat;

	i = 0;
	while(1)
	{
		if (i == philo->time.num)
			i = 0;
		pthread_mutex_lock(&philo[i].time.mutex);
		last_eat = philo->last_eat;
		pthread_mutex_unlock(&philo[i].time.mutex);
		if (get_time() >= last_eat + philo->time.die)
		{
			pthread_mutex_lock(&philo->time.print);
			printf("%zu	%d died\n", get_time() - philo->program_start, philo[i].id + 1);
			pthread_mutex_unlock(&philo->time.print);
			exit(1);
		}
		i++;
	}
}

void* routine(void *param)
{
	t_philo *philo = param;

	if ((philo->id) % 2 != 0)
	{
		sleeping(philo);
	}
	while(1)
	{
		thinking(philo);
		take_fork(philo);
		sleeping(philo);
	}
	return(0);
}

void	creat_threads(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->time.num)
	{
		philo[i].id = i;
		philo[i].time = philo->time;
		philo[i].forks = philo->forks;
		philo[i].program_start = philo->program_start;
		philo[i].last_eat = get_time();
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
		{
			printf("pthread create fails !!\n");
			exit(1);
		}
		usleep(40);
		i++;
	}
	check_time(philo);
	i = 0;
	while(i < philo->time.num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
void get_arguments(t_philo *philo, int ac, char **av)
{
	if (ac == 5)
	{
		philo->program_start = get_time();
		philo->time.num = get_info(av[1]);
		philo->time.die = get_info(av[2]);
		philo->time.eat = get_info(av[3]);
		philo->time.sleep = get_info(av[4]);
	}
	else 
		error("Error: invalid number of arguments\n");
}

int main(int ac, char **av)
{
	t_philo *philo;
	int i ;

	philo = malloc(get_info(av[1]) * sizeof(t_philo));
	if (!philo)
		return (1);
	memset(philo, 0, get_info(av[1]) * sizeof(t_philo));
	philo->forks = malloc(get_info(av[1]) * sizeof(pthread_mutex_t));
	if (!philo->forks)
		return (1);
	memset(philo->forks, 0, get_info(av[1]) * sizeof(pthread_mutex_t));
	get_arguments(philo, ac, av);
	pthread_mutex_init(&philo->time.print, NULL);
	pthread_mutex_init(&philo->time.mutex, NULL);
	i = 0;
	while (i < philo->time.num)
		pthread_mutex_init(&philo->forks[i++], NULL);
	creat_threads(philo);
	pthread_mutex_destroy(&philo->time.print);
	i = 0;
	while (i < philo->time.num)
		pthread_mutex_destroy(&philo->forks[i++]);
}
