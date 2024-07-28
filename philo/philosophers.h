/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arekoune <arekoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:30:10 by arekoune          #+#    #+#             */
/*   Updated: 2024/07/26 17:16:37 by arekoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mutex
{
	pthread_mutex_t	print;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	check_death;
	pthread_mutex_t	finish;
}					t_mutex;

typedef struct s_data
{
	long			n_philo;
	long			tm_die;
	long			tm_eat;
	long			tm_sleep;
	size_t			program_start;
	int				is_dead;
	long			is_finish;
	long			n_meal;
	char			flag;
	t_mutex			mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	long			is_enough;
	t_data			*data;
	size_t			last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*forks;
	pthread_t		thread;
}					t_philo;

// utils.c
int					error(char *str);
size_t				get_time(void);
long				ft_atoi(char *str);
int					ft_sleep(long time, t_philo *philo);
int					ft_print(t_philo *philo, char *str);

// philo.c
int					initial_mutexs(t_philo *philo);
int					get_data(t_philo *philo, int ac, char **av);
int					creat_thread(t_philo *philo);
void				checking_time(t_philo *philo);

// routine.c
int					thinking(t_philo *philo);
int					eating(t_philo *philo);
int					take_forks(t_philo *philo);
int					sleeping(t_philo *philo);
void				*routine(void *argum);

// utils2.c
int					check_death(t_philo *philo);
void				asign_forks(t_philo *philo);
void				free_ressources(t_philo *philo);
int					malloc_fails(t_philo *philo);

#endif