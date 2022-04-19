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
		args->add_nbr = 0;
}

void	init_table(t_table *table)
{
	int	i;

	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->args->nbr);
	i = 0;
	while ( i < table->args->nbr)
	{
		if (pthread_create(&table->philo[i]->id, NULL, (void*)printf, NULL) != 0)
			error("Error: threads problem.\n");
	}
}

int main (int argc, char **argv)
{
	t_arguments	*args;
	t_table	table;
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	args = (t_arguments *)malloc(sizeof(t_arguments));
	check_arguments(argc, argv);
	init_arguments(args, argc, argv);
	
	return (0);
}
