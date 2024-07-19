/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:30:14 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/19 18:50:46 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static	void	*dinner(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(50);
	while (philo->vars->death == 0)
	{
		// hacer el bucle
		// que agarre fork left, right
		// que coma
		// que duerma
		// que piense
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
	}
	i = -1;
	while (++i < vars->n_philo)
	{
		pthread_create(&philo[i].thread, NULL, dinner, (void *)&philo);
		// manejar el error cuando se crea el hilo y falla.
		pthread_join(philo->thread, NULL);
	}
}
