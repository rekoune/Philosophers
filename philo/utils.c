#include "philo.h"

void error(char *str)
{
	printf("%s", str);
	exit(1);
}

void ft_sleep(int time)
{
	size_t current_time;
	size_t time_end;

	current_time = get_time();
	time_end = current_time + time;
	while(time_end > get_time())
	{
		usleep(150);
	}
}
