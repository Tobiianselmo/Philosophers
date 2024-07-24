/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:35:16 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/24 18:14:11 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/* int	get_tt_die(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->vars->last_meal_mtx);
	if (philo->vars->t_die < (get_time() - philo->vars->start) - philo[i].last_meal)
	{
		pthread_mutex_unlock(&philo->vars->last_meal_mtx);
	}
	return (0);
} */

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

/* static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
} */

void	write_action(t_philo *philo, char *action)
{
	if (get_death(philo->vars) == 0)
	{
		pthread_mutex_lock(&philo->vars->write_mtx);
		printf("%ld %d %s\n", (get_time() - philo->vars->start), philo->id, action);
		pthread_mutex_unlock(&philo->vars->write_mtx);
	}
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
