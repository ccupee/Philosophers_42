/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:49:40 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/18 19:49:42 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_arguments(t_arguments *args, int argc, char **argv)
{
	args->nbr = ft_atoi(argv[1]);
	args->die = ft_atoi(argv[2]);
	args->eat = ft_atoi(argv[3]);
	args->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->add_nbr = ft_atoi(argv[5]);
	else
		args->add_nbr = -1;
}

int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args->nbr)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0)
		{
			printf("Error: problems with mutex\n");
			return (0);
		}
	}
	return (1);
}

void	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	table->args = (t_arguments *)malloc(sizeof(t_arguments));
	init_arguments(table->args, argc, argv);
	init_forks(table);/////integer
	i = -1;
	while (++i < table->args->nbr)
	{
		table->philos[i].nbr = i;
		table->philos[i].right = i;
		table->philos[i].left = (i + 1) % (table->args->nbr);
	}
}

long	get_current_time(void)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	return ((tmp.tv_sec * 1000) + (tmp.tv_usec / 1000));
}

long	get_time(t_philo *philo)
{
	return (get_current_time() - philo->time);
}

void	ft_usleep(long wait)
{
	long	time;

	time = get_current_time();
	while (get_current_time() < time + wait)
		usleep(100);
}

int	init_threads(t_table *table, int argc, char **argv)
{
	int	i;

	i = -1;
	init_table(table, argc, argv);
	while (++i < table->args->nbr)
	{
		table->philos[i].flag = 0;
		table->philos[i].time = get_current_time();
		table->philos[i].times_to_eat = 0;
		table->num = i;
		if (pthread_create(&(table->philos[i].id), NULL, ft_philo, (void *)(table)) != 0)
		{
			printf("Error: threads problem.\n");
			return(0);
		}
		table->philos[i].time = get_current_time();
	}
	table->num = -1;
}

void	skip(int n)
{
	if (n % 2)
		usleep(150);
}

void	print(t_table *table, int nbr, char *str)
{
	if (table->philos[table->num].flag == 0)
	{
		pthread_mutex_lock(&(table->forks[nbr]));
		printf("%ld %d %s\n", get_time(&(table->philos[table->num])), table->num + 1, str);
		pthread_mutex_unlock(&(table->forks[nbr]));
	}
}

int	for_one(t_table *table)
{
	if (table->args->nbr == 1)
	{
		pthread_mutex_unlock(&(table->forks[table->philos[table->num].right]));
		return (1);
	}
	return (0);
}
void	sleep_think(t_table *table)
{
	print(table, table->num, " is sleeping");
	ft_usleep(table->args->sleep);
	print(table, table->num, " is thinking");
}

void	*ft_philo(void *data)
{
	t_table *table;
	t_philo	cur_philo;

	table = (t_table *)data;
	cur_philo = table->philos[table->num];
	skip(table->num);
	while (cur_philo.flag == 0)
	{
		pthread_mutex_lock(&(table->forks[cur_philo.right]));
		print(table, table->num, " has taken a fork");
		if (for_one(table))
			break;
		pthread_mutex_lock(&(table->forks[cur_philo.left]));
		//print(table, table->num, " has taken a fork");
		print(table, table->num, " is eating");
		cur_philo.time = get_current_time();
		ft_usleep(table->args->eat);
		pthread_mutex_unlock(&(table->forks[cur_philo.right]));
		pthread_mutex_unlock(&(table->forks[cur_philo.left]));
		table->philos[table->num].times_to_eat++;
		if (table->args->add_nbr == -1)
			break;
		sleep_think(table);
	}
}

int main (int argc, char **argv)
{
	t_table *table;

	if (!check_arguments(argc, argv))
		return (0);
	table = (t_table *)malloc(sizeof(t_table));
	// table->args = (t_arguments *)malloc(sizeof(t_arguments));
	// init_arguments((table->args), argc, argv);
	// printf("%d %d %d %d\n", table->args->nbr, table->args->die, table->args->eat, table->args->sleep);
	init_table(table, argc, argv);
	printf("%d %d %d %d\n", table->args->nbr, table->args->die, table->args->eat, table->args->sleep);
	init_forks(table);
	return (0);
}
