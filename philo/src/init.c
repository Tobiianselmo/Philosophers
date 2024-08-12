/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:53:42 by tanselmo          #+#    #+#             */
/*   Updated: 2024/08/09 18:52:28 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	init_num(t_vars *data)
{
	data->n_philo = -1;
	data->t_die = -1;
	data->t_eat = -1;
	data->t_sleep = -1;
	data->must_eat = -1;
}

static int	set_num(t_vars *data, int i, char *line)
{
	int	nbr;

	nbr = atoi_phil(line);
	if (nbr == -1 || (nbr == 0 && i != 5))
	{
		write(2, "Error: wrong arguments\n", 24);
		return (0);
	}
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

static int	init_mutex(t_vars *data)
{
	if (pthread_mutex_init(&data->write_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->death_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->last_meal_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->num_meals_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->finish_meal_mtx, NULL))
		return (0);
	return (1);
}

int	init_struct(t_vars *data, char **argv)
{
	int	i;	

	i = 1;
	init_num(data);
	while (argv[i])
	{
		if (set_num(data, i, argv[i]) == 0)
			return (0);
		i++;
	}
	if (data->must_eat != -1)
		data->bool_meals = true;
	else
		data->bool_meals = false;
	data->death = 0;
	data->start = 0;
	data->finish_meal = 0;
	data->create_threads = false;
	if (init_mutex(data) == 0)
	{
		write(2, "Error: initializing mutex\n", 27);
		return (0);
	}
	return (1);
}

void	init_philos(t_philo *p, t_vars *vars, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < vars->n_philo)
	{
		p[i].id = i + 1;
		p[i].l_fork = &forks[i];
		p[i].r_fork = &forks[(i + 1) % vars->n_philo];
		p[i].last_meal = 0;
		p[i].num_meals = 0;
		p[i].leave_dinner_table = 0;
		p[i].vars = vars;
		p[i].write_mtx = &vars->write_mtx;
		p[i].death_mtx = &vars->death_mtx;
		p[i].last_meal_mtx = &vars->last_meal_mtx;
		p[i].num_meals_mtx = &vars->num_meals_mtx;
		p[i].finish_meal_mtx = &vars->finish_meal_mtx;
	}
}
