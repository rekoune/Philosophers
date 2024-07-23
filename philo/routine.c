/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:30:13 by arekoune          #+#    #+#             */
/*   Updated: 2024/07/23 20:41:58 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.check_death);
	if (philo->data.is_dead == 1 || (philo->data.is_finish == philo->data.n_philo && philo->data.flag == 'y'))
		return(0);
	pthread_mutex_unlock(&philo->mutex.check_death);
	pthread_mutex_lock(&philo->mutex.print);
	printf("%zu	%d is thinking\n", get_time() - philo->data.program_start, philo->id);
	pthread_mutex_unlock(&philo->mutex.print);
	return(1);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.check_death);
	if (philo->data.is_dead == 1 || (philo->data.is_finish == philo->data.n_philo && philo->data.flag == 'y'))
		return(0);
	philo->is_enough++;
	pthread_mutex_unlock(&philo->mutex.check_death);
	pthread_mutex_lock(&philo->mutex.meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex.meal_lock);
	pthread_mutex_lock(&philo->mutex.print);
	printf("%zu	%d is eating\n", get_time() - philo->data.program_start, philo->id);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_sleep(philo->data.tm_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return(1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.check_death);
	if (philo->data.is_dead == 1 || (philo->data.is_finish == philo->data.n_philo && philo->data.flag == 'y'))
		return(0);
	pthread_mutex_unlock(&philo->mutex.check_death);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->mutex.print);
	printf("%zu	%d has taken a fork\n", get_time() - philo->data.program_start, philo->id);
	pthread_mutex_unlock(&philo->mutex.print);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->mutex.print);
	printf("%zu	%d has taken a fork\n", get_time() - philo->data.program_start, philo->id);
	pthread_mutex_unlock(&philo->mutex.print);
	if (!eating(philo))
		return(0);
	return(1);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.check_death);
	if (philo->data.is_dead == 1 || (philo->data.is_finish == philo->data.n_philo && philo->data.flag == 'y'))
		return(0);
	pthread_mutex_unlock(&philo->mutex.check_death);
	pthread_mutex_lock(&philo->mutex.print);
	printf("%zu	%d is sleeping\n", get_time() - philo->data.program_start, philo->id);
	pthread_mutex_unlock(&philo->mutex.print);
	ft_sleep(philo->data.tm_sleep);
	return(1);
}

void	*routine(void *argum)
{
	t_philo *philo;

	philo = argum;
	if (philo->id % 2 != 0)
		sleeping(philo);
	while(1)
	{
		pthread_mutex_lock(&philo->mutex.test);
		pthread_mutex_unlock(&philo->mutex.test);
		pthread_mutex_lock(&philo->mutex.check_death);
		if (philo->data.is_dead == 1)
			return(NULL);
		pthread_mutex_unlock(&philo->mutex.check_death);
		if (!thinking(philo))
			return(NULL);
		if (!take_forks(philo))
			return(NULL);
		if (!sleeping(philo))
			return(NULL);
		if (philo->data.is_finish == philo->data.n_philo && philo->data.flag == 'y')
			return(NULL);
	}
	return(NULL);
}
