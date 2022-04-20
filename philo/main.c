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

int	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	table->args = (t_arguments *)malloc(sizeof(t_arguments));
	init_arguments(table->args, argc, argv);
	table->philo = (t_philo **)malloc(sizeof(t_philo *) * table->args->nbr);
	i = -1;
	while (++i < table->args->nbr)
	{
		table->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (pthread_create(&(table->philo[i]->id), NULL, (void*)printf, NULL) != 0)
		{
			printf("Error: threads problem.\n");
			return(0);
		}
	}
	return (1);
}

int main (int argc, char **argv)
{
	t_table	table;

	if (!check_arguments(argc, argv))
		return (0);
	init_table(&table, argc, argv);
	return (0);
}
