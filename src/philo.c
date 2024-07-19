/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:24:40 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/19 18:37:57 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//1 number_of_philosophers (Tambien el Num de tenedores)
//2 time_to_die (tiempo que puede estar sin comer)
//3 time_to_eat (tiempo para comer, y que tiene los tenedores ocupados)
//4 time_to_sleep (tiempo que tiene para dormir)
//5 [number_of_times_each_philosopher_must_eat] ((OPCIONAL), es la cantidad de veces que tienen que comer)

static pthread_mutex_t	*init_forks(int len)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * len);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
			return (NULL);
	}
	return (forks);
}

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_philo			philo;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error arguments number\n", 24);
		return (2);
	}
	if (init_struct(&vars, argv) == 0)
		return (0);
	forks = init_forks(vars.n_philo);
	create_threads(&philo, &vars, forks);
	return (0);
}
