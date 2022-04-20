/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:50:24 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/18 19:50:26 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef pthread_mutex_t mutex_t;

typedef struct s_arguments
{
	int nbr;
	int	die;
	int	eat;
	int	sleep;
	int	add_nbr;
}	t_arguments;

typedef struct s_philo
{
	pthread_t		id;
	mutex_t			right;
	mutex_t			left;
}	t_philo;

typedef struct s_table
{
	t_arguments *args;
	t_philo		**philo;
}	t_table;


int		ft_atoi(const char *str);

void	error(char *str);

int		ft_isdigit(int c);

int	check_arguments(int argc, char **argv);

#endif
