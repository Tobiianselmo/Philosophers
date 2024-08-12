/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:46:51 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/06 16:56:31 by tanselmo         ###   ########.fr       */
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

bool	init_simulation(t_philo *philo, t_vars *vars, pthread_mutex_t *forks)
{
	pthread_t	hawk;
	int			i;
	int			join;

	i = -1;
	join = 0;
	philo->vars->start = get_time();
	if (pthread_create(&hawk, NULL, &hawk_eye, (void *)philo))
	{
		free_msg("breeding hawk\n", philo, forks);
		return (false);
	}
	set_philo(philo, vars, forks);
	if (vars->create_threads == true)
	{
		if (pthread_join(hawk, NULL))
			join = 1;
		while (++i < philo->vars->n_philo)
			if (pthread_join(philo[i].thread, NULL))
				join = 1;
	}
	if (join == 1)
		return (false);
	return (true);
}
