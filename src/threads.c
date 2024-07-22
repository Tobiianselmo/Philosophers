/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:30:14 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/22 19:36:57 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	*dinner(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(philo->l_fork);
		write_action(philo, FORK);
		pthread_mutex_lock(philo->r_fork);
		write_action(philo, FORK);
		write_action(philo, EAT);
		eat_time(philo, philo->vars->t_eat);
		philo->num_meals++;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		write_action(philo, SLEEP);
		sleep_time(philo->vars->t_sleep);
		write_action(philo, THINK);
		usleep(70);
	}
}

void	create_threads(t_philo *philo, t_vars *vars, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * (vars->n_philo + 1));
	if (!philo)
		return ;
	while (++i < vars->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % vars->n_philo];
		philo[i].last_meal = 0;
		philo[i].num_meals = 0;
		philo[i].vars = vars;
		philo[i].write = &vars->write;
	}
	i = -1;
	vars->start = get_time();
	while (++i < vars->n_philo)
	{
		pthread_create(&philo[i].thread, NULL, &dinner, (void *)&philo[i]);
		// manejar el error cuando se crea el hilo y falla.
	}
	pthread_join(philo->thread, NULL);
}
