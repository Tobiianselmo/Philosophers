/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:24:40 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/30 13:52:45 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	dead_or_alive(t_philo *philo, int i)
{
	protect_mutex(LOCK, &philo->vars->finish_meal_mtx);
	if (philo[i].leave_dinner_table == 0)
	{
		protect_mutex(UNLOCK, &philo->vars->finish_meal_mtx);
		protect_mutex(LOCK, &philo->vars->last_meal_mtx);
		if (philo->vars->t_die < (get_time() - philo->vars->start)
			- philo[i].last_meal)
		{
			protect_mutex(UNLOCK, &philo->vars->last_meal_mtx);
			write_action(&philo[i], DIED);
			set_death(philo->vars, 1);
			return (0);
		}
		protect_mutex(UNLOCK, &philo->vars->last_meal_mtx);
	}
	else
		protect_mutex(UNLOCK, &philo->vars->finish_meal_mtx);
	return (1);
}

static void	*hawk_eye(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (get_death(philo->vars) == 0)
	{
		i = -1;
		while (++i < philo->vars->n_philo)
		{
			if (dead_or_alive(philo, i) == 0)
				return (NULL);
			protect_mutex(LOCK, philo[i].finish_meal_mtx);
			if (philo[i].vars->finish_meal == philo->vars->n_philo)
			{
				protect_mutex(UNLOCK, philo[i].finish_meal_mtx);
				return (NULL);
			}
			protect_mutex(UNLOCK, philo[i].finish_meal_mtx);
		}
		usleep(50);
	}
	return (NULL);
}

pthread_mutex_t	*init_forks(int len)
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

static int	set_all(char **argv, int i)
{
	t_vars			vars;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_t		hawk;

	if (init_struct(&vars, argv) == 0)
		return (0);
	forks = init_forks(vars.n_philo);
	if (!forks)
		return (0);
	philo = set_philo(&vars, forks);
	if (!philo)
		return (0);
	if (pthread_create(&hawk, NULL, &hawk_eye, (void *)philo))
	{
		free_msg("breeding hawk\n", philo, forks);
		return (0);
	}
	if (pthread_join(hawk, NULL))
		return (0);
	while (++i < philo->vars->n_philo)
		if (pthread_join(philo[i].thread, NULL))
			return (0);
	the_end(vars, forks, philo);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (set_all(argv, -1) == 0)
			return (1);
	}
	else
	{
		write(2, "Error: wrong arguments number\n", 31);
		return (1);
	}
	return (0);
}
