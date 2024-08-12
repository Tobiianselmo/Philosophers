/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:35:16 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/09 18:52:31 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	write_action(t_philo *philo, char *action)
{
	protect_mutex(LOCK, &philo->vars->write_mtx);
	if (get_death(philo->vars) == 0)
	{
		printf("%ld %d %s\n",
			(get_time() - philo->vars->start), philo->id, action);
	}
	protect_mutex(UNLOCK, &philo->vars->write_mtx);
}

void	sleepy_time(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
}

int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	the_end(t_vars vars, pthread_mutex_t *forks, t_philo *p)
{
	int	i;

	i = -1;
	while (++i < vars.n_philo)
		protect_mutex(DESTROY, &forks[i]);
	protect_mutex(DESTROY, &vars.finish_meal_mtx);
	protect_mutex(DESTROY, &vars.num_meals_mtx);
	protect_mutex(DESTROY, &vars.last_meal_mtx);
	protect_mutex(DESTROY, &vars.death_mtx);
	protect_mutex(DESTROY, &vars.write_mtx);
	free(forks);
	free(p);
}
