/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:30:14 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/25 19:22:50 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	unstarvation(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		write_action(philo, FORK);
		pthread_mutex_lock(philo->r_fork);
		write_action(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		write_action(philo, FORK);
		pthread_mutex_lock(philo->l_fork);
		write_action(philo, FORK);
	}
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
}

static void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(50);
	while (get_death(philo->vars) == 0 && check_bool(philo) == true)
	{
		unstarvation(philo);
		write_action(philo, SLEEP);
		sleepy_time(philo->vars->t_sleep);
		write_action(philo, THINK);
	}
	return (NULL);
}

static void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->l_fork);
	write_action(philo, FORK);
	pthread_mutex_unlock(philo->l_fork);
	sleepy_time(philo->vars->t_die);
	return (NULL);
}

t_philo	*create_threads(t_vars *vars, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * vars->n_philo);
	if (!philo)
		return (NULL);
	init_philos(philo, vars, forks);
	i = -1;
	vars->start = get_time();
	while (++i < vars->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&dinner, (void *)&philo[i]))
			return (NULL); //funcion de error
	}
	return (philo);
}

t_philo	*set_philo(t_vars *vars, pthread_mutex_t *forks)
{
	t_philo	*philo;

	if (vars->n_philo == 1)
	{
		philo = (t_philo *)malloc(sizeof(t_philo) * vars->n_philo);
		if (!philo)
			return (NULL);
		init_philos(philo, vars, forks);
		vars->start = get_time();
		if (pthread_create(&philo[0].thread, NULL,
				&one_philo, (void *)&philo[0]))
			return (NULL); //funcion de error
	}
	else
		philo = create_threads(vars, forks);
	return (philo);
}
