/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:24:40 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/12 15:17:05 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

pthread_mutex_t	*init_forks(int len)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * len);
	if (!forks)
	{
		free_msg("creating forks\n", NULL, NULL);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
		{
			free_msg("initializing forks\n", NULL, forks);
			return (NULL);
		}
	}
	return (forks);
}

static t_philo	*create_philos(t_vars *vars, pthread_mutex_t *forks)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * vars->n_philo);
	if (!philo)
	{
		free_msg("malloc error\n", NULL, forks);
		return (NULL);
	}
	init_philos(philo, vars, forks);
	return (philo);
}

static int	set_all(char **argv)
{
	t_vars			vars;
	pthread_mutex_t	*forks;
	t_philo			*philo;

	if (init_struct(&vars, argv) == 0)
		return (0);
	if (vars.must_eat == 0)
		return (1);
	forks = init_forks(vars.n_philo);
	if (!forks)
		return (0);
	philo = create_philos(&vars, forks);
	if (!philo)
		return (0);
	if (init_simulation(philo, &vars, forks) == false)
	{
		the_end(vars, forks, philo);
		return (0);
	}
	the_end(vars, forks, philo);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (set_all(argv) == 0)
			return (1);
	}
	else
	{
		write(2, "Error: wrong arguments number\n", 31);
		return (1);
	}
	return (0);
}
