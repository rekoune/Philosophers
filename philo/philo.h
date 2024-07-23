#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data{
	long	n_philo;
	long	tm_die;
	long	tm_eat;
	long	tm_sleep;
	size_t	program_start;
	int		is_dead;
	long	n_meal;
}			t_data;

typedef struct s_mutex{
	pthread_mutex_t print;
	pthread_mutex_t meal_lock;
	pthread_mutex_t check_death;
}			t_mutex;

typedef struct s_philo{
	int				id;
	t_data			data;
	t_mutex			mutex;
	size_t			last_meal;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_t		thread;
}			t_philo;


//utils.c
int		error(char *str);
size_t	get_time();
long	ft_atoi(char *str);
void	ft_sleep(long time);

//philo.c
int		initial_mutexs(t_philo *philo);
int		get_data(t_philo *philo, int ac, char **av);
int		creat_thread(t_philo *philo);
int		checking_time(t_philo *philo);

//routine.c
int		thinking(t_philo *philo);
int		eating(t_philo *philo);
int		take_forks(t_philo *philo);
int		sleeping(t_philo *philo);
void	*routine(void *argum);


#endif