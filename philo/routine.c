#include "philo.h"

void thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->time.print);
	printf("%zu	%d is thinking\n", get_time()- philo->program_start, philo->id + 1);
	pthread_mutex_unlock(&philo->time.print);
}
void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->id]);
	pthread_mutex_lock(&philo->time.print);
	printf("%zu	%d has taken a fork\n", get_time()- philo->program_start, philo->id + 1);
	pthread_mutex_unlock(&philo->time.print);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->forks[philo->time.num - 1]);
	else
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->time.print);
	printf("%zu	%d has taken a fork\n", get_time() - philo->program_start, philo->id + 1);
	pthread_mutex_unlock(&philo->time.print);
	eating(philo);
}
void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->time.mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->time.mutex);
	pthread_mutex_lock(&philo->time.print);
	printf("%zu	%d is eating\n", get_time()- philo->program_start, philo->id + 1);
	pthread_mutex_unlock(&philo->time.print);
	ft_sleep(philo->time.eat);
	pthread_mutex_unlock(&philo->forks[philo->id]);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->forks[philo->time.num - 1]);
	else
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
}
void sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->time.print);
	printf("%zu	%d is sleeping\n", get_time() - philo->program_start, philo->id + 1);
	pthread_mutex_unlock(&philo->time.print);
	ft_sleep(philo->time.sleep);
}
