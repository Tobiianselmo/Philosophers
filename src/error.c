/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:15:02 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/30 10:46:29 by tanselmo         ###   ########.fr       */
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
	if (philo)
		free(philo);
	if (forks)
		free(forks);
	write(2, "Error: ", 8);
	write(2, msg, ft_strlen(msg));
}
