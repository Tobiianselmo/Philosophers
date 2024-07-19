/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:41:52 by tanselmo          #+#    #+#             */
/*   Updated: 2024/07/19 18:46:49 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_vars
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			must_eat;
	int			death;
	long		time;
}	t_vars;

typedef struct	s_philo
{
	int				id;
	int				num_meals;
	long			last_meal;
	pthread_t		*thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_vars			*vars;
}	t_philo;

//-------------INIT------------//
int		init_struct(t_vars *data, char **argv);
//-------------ATOI------------//
int		atoi_phil(char *str);

#endif