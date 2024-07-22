/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:35:16 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/22 18:38:23 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	write_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->vars->write);
	printf("%ld %d %s\n", (get_time() - philo->vars->start), philo->id, action);
	pthread_mutex_unlock(&philo->vars->write);
}

void	eat_time(t_philo *philo, int time)
{
	philo->last_meal = get_time() - philo->vars->start;
	sleep_time(time);
}

void	sleep_time(int time)
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
