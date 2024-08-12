/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:57:11 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/09 18:51:29 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		protect_mutex(LOCK, philo->l_fork);
		write_action(philo, FORK);
		protect_mutex(LOCK, philo->r_fork);
		write_action(philo, FORK);
	}
	else
	{
		protect_mutex(LOCK, philo->r_fork);
		write_action(philo, FORK);
		protect_mutex(LOCK, philo->l_fork);
		write_action(philo, FORK);
	}
}

int	get_death(t_vars *vars)
{
	int	dead;

	protect_mutex(LOCK, &vars->death_mtx);
	dead = vars->death;
	protect_mutex(UNLOCK, &vars->death_mtx);
	return (dead);
}

void	set_death(t_vars *vars, int death)
{
	protect_mutex(LOCK, &vars->death_mtx);
	vars->death = death;
	protect_mutex(UNLOCK, &vars->death_mtx);
}

bool	check_bool(t_philo *philo)
{
	if (philo->vars->bool_meals == false)
		return (true);
	protect_mutex(LOCK, &philo->vars->num_meals_mtx);
	if (philo->num_meals < philo->vars->must_eat)
	{
		protect_mutex(UNLOCK, &philo->vars->num_meals_mtx);
		return (true);
	}
	else
	{
		protect_mutex(UNLOCK, &philo->vars->num_meals_mtx);
		return (false);
	}
}
