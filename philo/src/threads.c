/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:30:14 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/09 18:57:17 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	unstarvation(t_philo *philo)
{
	take_forks(philo);
	write_action(philo, EAT);
	protect_mutex(LOCK, &philo->vars->last_meal_mtx);
	philo->last_meal = (get_time() - philo->vars->start);
	protect_mutex(UNLOCK, &philo->vars->last_meal_mtx);
	protect_mutex(LOCK, &philo->vars->num_meals_mtx);
	philo->num_meals++;
	protect_mutex(UNLOCK, &philo->vars->num_meals_mtx);
	sleepy_time(philo->vars->t_eat);
	protect_mutex(UNLOCK, philo->l_fork);
	protect_mutex(UNLOCK, philo->r_fork);
}

static void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		usleep(50);
	while (get_death(philo->vars) == 0 && check_bool(philo) == true)
	{
		unstarvation(philo);
		if (check_bool(philo) == false)
		{
			protect_mutex(LOCK, &philo->vars->finish_meal_mtx);
			philo->vars->finish_meal++;
			philo->leave_dinner_table = 1;
			protect_mutex(UNLOCK, &philo->vars->finish_meal_mtx);
			return (NULL);
		}
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
	if (check_bool(philo) == true)
	{
		protect_mutex(LOCK, philo->l_fork);
		write_action(philo, FORK);
		protect_mutex(UNLOCK, philo->l_fork);
		sleepy_time(philo->vars->t_die);
	}
	return (NULL);
}

bool	create_threads(t_philo *philo, t_vars *vars, pthread_mutex_t *forks)
{
	int		i;

	i = -1;
	while (++i < vars->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&dinner, (void *)&philo[i]))
		{
			free_msg("creating threads\n", philo, forks);
			return (false);
		}
	}
	return (true);
}

bool	set_philo(t_philo *philo, t_vars *vars, pthread_mutex_t *forks)
{
	if (vars->n_philo == 1)
	{
		if (pthread_create(&philo[0].thread, NULL,
				&one_philo, (void *)&philo[0]))
		{
			free_msg("creating threads\n", philo, forks);
			return (false);
		}
	}
	else if (create_threads(philo, vars, forks) == false)
		return (false);
	vars->create_threads = true;
	return (true);
}
