#include "philo.h"

void	init_philo(t_philo *philo, int argc, char **argv)
{
	philo->args = (t_arguments *)malloc(sizeof(t_arguments));
	philo->args->nbr = ft_atoi(argv[1]);
	philo->args->die = ft_atoi(argv[2]);
	philo->args->eat = ft_atoi(argv[3]);
	philo->args->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->args->add_nbr = ft_atoi(argv[5]);
	else
		philo->args->add_nbr = 0;
}

int main (int argc, char **argv)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	check_arguments(argc, argv);
	init_philo(philo, argc, argv);
	
	return (0);
}
