/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:35:16 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/25 19:18:40 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	write_action(t_philo *philo, char *action)
{
	if (get_death(philo->vars) == 0)
	{
		pthread_mutex_lock(&philo->vars->write_mtx);
		printf("%ld %d %s\n",
			(get_time() - philo->vars->start), philo->id, action);
		if (ft_strcmp(action, "died"))
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
