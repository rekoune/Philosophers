#include "philo.h"

int	checking_time(t_philo *philo)
{
	int	i;
	size_t last_meal;

	i = 0;
	while(1)
	{
		if (i == philo->data.n_philo)
			i = 0;
		pthread_mutex_lock(&philo[i].mutex.meal_lock);
		last_meal = philo[i].last_meal;
		pthread_mutex_unlock(&philo[i].mutex.meal_lock);
		if(get_time() > (last_meal + philo->data.tm_die))
		{
			pthread_mutex_lock(&philo->mutex.check_death);
			philo->data.is_dead = 1;
			pthread_mutex_unlock(&philo->mutex.check_death);
			pthread_mutex_lock(&philo[i].mutex.print);
			printf("%zu	%d died\n", get_time() - philo->data.program_start, philo[i].id);
			pthread_mutex_unlock(&philo[i].mutex.print);
			return(0);
		}
		i++;
	}
	return(1);
}

int	initial_mutexs(t_philo *philo)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(philo->data.n_philo * sizeof(pthread_mutex_t));
	if(!forks)
		return(0);
	while(i < philo->data.n_philo)
		pthread_mutex_init(&forks[i++], NULL);
	pthread_mutex_init(&philo->mutex.print, NULL);
	pthread_mutex_init(&philo->mutex.meal_lock, NULL);
	pthread_mutex_init(&philo->mutex.check_death, NULL);
	i = 0;
	while(i < philo->data.n_philo - 1)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = &forks[i + 1];
		philo[i].left_fork = &forks[i];
		i++;
	}
	philo[i].id = i + 1;
	philo[i].right_fork = &forks[0];
	philo[i].left_fork = &forks[i];
	return(1);
}

int	get_data(t_philo *philo, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return(error("Error : Invalid arguments\n"));
	philo->data.n_philo = ft_atoi(av[1]);
	if (philo->data.n_philo == -1)
		return(0);
	philo->data.tm_die = ft_atoi(av[2]);
	if (philo->data.tm_die == -1)
		return(0);
	philo->data.tm_eat = ft_atoi(av[3]);
	if (philo->data.tm_eat == -1)
		return(0);
	philo->data.tm_sleep = ft_atoi(av[4]);
	if (philo->data.tm_sleep == -1)
		return(0);
	if (ac == 6)
	{
		philo->data.n_meal = ft_atoi(av[5]);
		if (philo->data.n_meal == -1)
			return(0);
	}
	philo->data.program_start = get_time();
	philo->data.is_dead = 0;
	return(initial_mutexs(philo));
}

int	creat_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->data.n_philo)
	{
		philo[i].data =  philo->data;
		philo[i].mutex = philo->mutex;
		philo[i].last_meal = philo->data.program_start;
		i++;
	}
	i = 0;
	while(i < philo->data.n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
		{
			printf("Error: pthread create fails\n");
			return(0);
		}
		i++;
	}
	checking_time(philo);
	i = 0;
	while(i < philo->data.n_philo)
		pthread_detach(philo[i++].thread);
	return(1);
}

int main (int ac , char **av)
{
	t_philo *philo;

	if (ft_atoi(av[1]) == -1)
		return(1);
	philo = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	if (!philo)
	{
		printf("Error: malloc fails\n");
		return(1);
	}
	if (!get_data(philo, ac, av))
	{
		free(philo);
		return(1);
	}
	if (!creat_thread(philo))
		return(1);
	return(0);
}
