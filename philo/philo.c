/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:30:01 by arekoune          #+#    #+#             */
/*   Updated: 2024/07/25 13:23:54 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checking_time(t_philo *philo)
{
	int		i;
	size_t	last_meal;

	i = 0;
	while (1)
	{
		if (i == philo->data->n_philo)
			i = 0;
		pthread_mutex_lock(&philo[i].data->mutex.meal_lock);
		last_meal = philo[i].last_meal;
		pthread_mutex_unlock(&philo[i].data->mutex.meal_lock);
		if (get_time() > (last_meal + philo->data->tm_die))
		{
			ft_print(philo, "\033[1;31mdied\033[0m\n");
			pthread_mutex_lock(&philo->data->mutex.check_death);
			philo->data->is_dead = 1;
			pthread_mutex_unlock(&philo->data->mutex.check_death);
			return ;
		}
		if (!check_death(philo))
			return ;
		i++;
	}
	return ;
}

int	initial_mutexs(t_philo *philo)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(philo->data->n_philo * sizeof(pthread_mutex_t));
	if (!forks)
		return (0);
	while (i < philo->data->n_philo)
		pthread_mutex_init(&forks[i++], NULL);
	pthread_mutex_init(&philo->data->mutex.print, NULL);
	pthread_mutex_init(&philo->data->mutex.meal_lock, NULL);
	pthread_mutex_init(&philo->data->mutex.check_death, NULL);
	pthread_mutex_init(&philo->data->mutex.enough, NULL);
	pthread_mutex_init(&philo->data->mutex.finish, NULL);
	asign_forks(philo, forks);
	return (1);
}

int	get_data(t_philo *philo, int ac, char **av)
{
	if ((ac != 5 && ac != 6) || ft_atoi(av[1]) == 0)
		return (error("Error : Invalid arguments\n"));
	philo->data->n_philo = ft_atoi(av[1]);
	philo->data->tm_die = ft_atoi(av[2]);
	if (philo->data->tm_die == 0)
		return (error("Error : Invalid arguments\n"));
	philo->data->tm_eat = ft_atoi(av[3]);
	philo->data->tm_sleep = ft_atoi(av[4]);
	if (philo->data->n_philo == -1 || philo->data->tm_die == -1
		|| philo->data->tm_eat == -1 || philo->data->tm_sleep == -1)
		return (0);
	philo->data->flag = 'n';
	if (ac == 6)
	{
		philo->data->n_meal = ft_atoi(av[5]);
		if (philo->data->n_meal == -1)
			return (0);
		if (philo->data->n_meal == 0)
			return (error("Error : Invalid arguments\n"));
		philo->data->flag = 'y';
	}
	philo->data->program_start = get_time();
	philo->data->is_dead = 0;
	return (initial_mutexs(philo));
}

int	creat_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		philo[i].data = philo->data;
		philo[i].data->mutex = philo->data->mutex;
		philo[i].last_meal = philo->data->program_start;
		philo[i++].is_enough = 0;
	}
	i = 0;
	while (i < philo->data->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
		{
			printf("Error: pthread create fails\n");
			return (0);
		}
		i++;
	}
	checking_time(philo);
	i = 0;
	while (i < philo->data->n_philo)
		pthread_join(philo[i++].thread, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ft_atoi(av[1]) == -1)
		return (1);
	philo = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	philo->data = malloc(sizeof(t_data));
	if (!philo)
	{
		printf("Error: malloc fails\n");
		return (1);
	}
	if (!get_data(philo, ac, av))
	{
		free(philo);
		return (1);
	}
	if (!creat_thread(philo))
		return (1);
	return (0);
}
