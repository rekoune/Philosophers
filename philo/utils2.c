/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:14:46 by arekoune          #+#    #+#             */
/*   Updated: 2024/07/25 13:11:54 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.check_death);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex.check_death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex.check_death);
	pthread_mutex_lock(&philo->data->mutex.finish);
	if (philo->data->is_finish == philo->data->n_philo
		&& philo->data->flag == 'y')
	{
		pthread_mutex_unlock(&philo->data->mutex.finish);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex.finish);
	return (1);
}

void	asign_forks(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo - 1)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = &forks[i + 1];
		philo[i].left_fork = &forks[i];
		i++;
	}
	philo[i].id = i + 1;
	philo[i].right_fork = &forks[0];
	if (i == 0)
		philo[i].right_fork = NULL;
	philo[i].left_fork = &forks[i];
}
