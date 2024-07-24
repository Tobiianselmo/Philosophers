/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:30:14 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/24 18:17:00 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool	check_bool(t_philo *philo)
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

static void	*dinner(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(50);
	while (get_death(philo->vars) == 0 && check_bool(philo) == true)
	{
		pthread_mutex_lock(philo->l_fork);
		write_action(philo, FORK);
		pthread_mutex_lock(philo->r_fork);
		write_action(philo, FORK);
		write_action(philo, EAT);
		pthread_mutex_lock(&philo->vars->last_meal_mtx);
		philo->last_meal = (get_time() - philo->vars->start);
		pthread_mutex_unlock(&philo->vars->last_meal_mtx);
		pthread_mutex_lock(&philo->vars->num_meals_mtx);
		philo->num_meals++;
		pthread_mutex_unlock(&philo->vars->num_meals_mtx);
		sleepy_time(philo->vars->t_eat);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		write_action(philo, SLEEP);
		sleepy_time(philo->vars->t_sleep);
		write_action(philo, THINK);
	}
	return (NULL);
}

t_philo	*create_threads(t_vars *vars, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * vars->n_philo);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < vars->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % vars->n_philo];
		philo[i].last_meal = 0;
		philo[i].num_meals = 0;
		philo[i].vars = vars;
		philo[i].write_mtx = &vars->write_mtx;
		philo[i].death_mtx = &vars->death_mtx;
		philo[i].bool_mtx = &vars->bool_mtx;
		philo[i].last_meal_mtx = &vars->last_meal_mtx;
		philo[i].num_meals_mtx = &vars->num_meals_mtx;
	}
	i = -1;
	vars->start = get_time();
	while (++i < vars->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &dinner, (void *)&philo[i]))
			return (NULL);
	}
	return (philo);
}
