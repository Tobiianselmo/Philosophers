/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:15:02 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/06 11:28:47 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	free_msg(char *msg, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	if (philo)
	{
		if (philo->vars->create_threads == true)
		{
			while (++i < philo->vars->n_philo)
				if (pthread_join(philo[i].thread, NULL))
					return ;
		}
	}
	if (philo)
		free(philo);
	if (forks)
		free(forks);
	write(2, "Error: ", 8);
	write(2, msg, ft_strlen(msg));
}
