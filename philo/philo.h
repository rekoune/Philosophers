#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
#include <string.h>

 typedef struct s_time{
		int eat;
		int sleep;
		int die;
		int	num;
		pthread_mutex_t print;
		pthread_mutex_t mutex;
 }				t_time;

typedef struct s_philo{
	int id;
	size_t last_eat;
	size_t program_start;
	t_time time;
	pthread_mutex_t *forks;
	pthread_t thread;
}				t_philo;


// philo.c
int	get_info(char *str);
size_t get_time();
void check_time(t_philo *philo);
void* routine(void *param);
void	creat_threads(t_philo *philo);
void get_arguments(t_philo *philo, int ac, char **av);

// utils.c
void	error(char *str);
void	ft_sleep(int time);

// routine.c
void thinking(t_philo *philo);
void take_fork(t_philo *philo);
void eating(t_philo *philo);
void sleeping(t_philo *philo);


#endif