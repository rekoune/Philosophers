/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:30:13 by arekoune          #+#    #+#             */
/*   Updated: 2024/07/26 11:17:05 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	thinking(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	if (!ft_print(philo, "is thinking\n"))
		return (0);
	return (1);
}

int	eating(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	if (!ft_print(philo, "is eating\n"))
		return (0);
	ft_sleep(philo->data->tm_eat, philo);
	pthread_mutex_lock(&philo->data->mutex.meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->mutex.meal_lock);
	pthread_mutex_lock(&philo->data->mutex.enough);
	philo->is_enough++;
	pthread_mutex_lock(&philo->data->mutex.finish);
	if (philo->is_enough == philo->data->n_meal)
		philo->data->is_finish++;
	pthread_mutex_unlock(&philo->data->mutex.finish);
	pthread_mutex_unlock(&philo->data->mutex.enough);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (!ft_print(philo, "has taken a fork\n"))
		return (0);
	if (!philo->right_fork)
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (!ft_print(philo, "has taken a fork\n"))
		return (0);
	if (!eating(philo))
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	if (!ft_print(philo, "is sleeping\n"))
		return (0);
	if (!ft_sleep(philo->data->tm_sleep, philo))
		return (0);
	return (1);
}

void	*routine(void *argum)
{
	t_philo	*philo;

	philo = argum;
	if (philo->id % 2 != 0)
		sleeping(philo);
	while (1)
	{
		if (!thinking(philo))
			return (NULL);
		if (!take_forks(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
	}
	return (NULL);
}
