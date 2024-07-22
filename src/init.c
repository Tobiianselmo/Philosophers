/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:53:42 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/22 16:39:40 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


/* static void	init_num(t_vars *data)
{
	data->n_philo = -1;
	data->t_die = -1;
	data->t_eat = -1;
	data->t_sleep = -1;
	data->must_eat = -1;
} */

static int	set_num(t_vars *data, int i, char *line)
{
	int	nbr;

	nbr = atoi_phil(line);
	if (nbr == -1)
		return (0);
	if (i == 1)
		data->n_philo = nbr;
	else if (i == 2)
		data->t_die = nbr;
	else if (i == 3)
		data->t_eat = nbr;
	else if (i == 4)
		data->t_sleep = nbr;
	else if (i == 5)
		data->must_eat = nbr;
	return (1);
}

int	init_struct(t_vars *data, char **argv)
{
	int	i;	

	i = 1;
	while (argv[i])
	{
		if (set_num(data, i, argv[i]) == 0)
			return (0);
		i++;
	}
	data->death = 0;
	data->start = 0;
	return (1);
}
