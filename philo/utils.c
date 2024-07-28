/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:30:16 by arekoune          #+#    #+#             */
/*   Updated: 2024/07/28 10:20:50 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(long time, t_philo *philo)
{
	size_t	current_time;

	current_time = get_time();
	while ((current_time + time) > get_time())
	{
		if (!check_death(philo))
			return (0);
		usleep(300);
	}
	return (1);
}

int	error(char *str)
{
	printf("\033[1;31m%s\033[0m", str);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex.print);
	if (check_death(philo))
		printf("%zu	%d %s", get_time() - philo->data->program_start, philo->id,
			str);
	pthread_mutex_unlock(&philo->data->mutex.print);
	return (1);
}

long	ft_atoi(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (!str || !str[0])
	{
		error("Error : Invalid arguments\n");
		return (-1);
	}
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			error("Error : Invalid arguments\n");
			return (-1);
		}
		nb = nb * 10;
		nb = nb + (str[i] - 48);
		i++;
	}
	return (nb);
}
