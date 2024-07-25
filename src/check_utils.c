/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:57:11 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/25 17:30:17 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	get_death(t_vars *vars)
{
	int	dead;

	pthread_mutex_lock(&vars->death_mtx);
	dead = vars->death;
	pthread_mutex_unlock(&vars->death_mtx);
	return (dead);
}

void	set_death(t_vars *vars, int death)
{
	pthread_mutex_lock(&vars->death_mtx);
	vars->death = death;
	pthread_mutex_unlock(&vars->death_mtx);
}

bool	check_bool(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->bool_mtx);
	if (philo->vars->bool_meals == false)
	{
		pthread_mutex_unlock(&philo->vars->bool_mtx);
		return (true);
	}
	pthread_mutex_unlock(&philo->vars->bool_mtx);
	pthread_mutex_lock(&philo->vars->num_meals_mtx);
	if (philo->num_meals < philo->vars->must_eat)
	{
		pthread_mutex_unlock(&philo->vars->num_meals_mtx);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->vars->num_meals_mtx);
		return (false);
	}
}
