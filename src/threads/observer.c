/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:48:54 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/30 17:12:12 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	check_max_meals(t_philos *ph, int *finished_meals)
{
	pthread_mutex_lock(ph->meals_lock);
	if (ph->current_meals == *ph->max_meals)
		++finished_meals;
	pthread_mutex_unlock(ph->meals_lock);
}

inline static int check_time_die(t_philos *ph)
{
	size_t		time;
	bool		i;

	pthread_mutex_lock(ph->meals_lock);
	time = get_current_time() - ph->start_time;
	i = time - ph->time_lmeal > *ph->time_die;
	pthread_mutex_unlock(ph->meals_lock);
	return (i);
}

static int	check_time(t_philos *ph, int *finished_meals)
{	
	if (check_time_die(ph))
	{
		set_dead_flag(1, ph);
		dead_write(ph);
		return (1);
	}
	check_max_meals(ph, finished_meals);
	return (0);
}

void	*check_deaths(void *prog)
{
	t_program	*pr;
	int			i;
	int			finished_meals;

	pr = (t_program	*)prog;
	finished_meals = 0;
	while (true)
	{
		i = -1;
		while (++i < pr->nb_philos)
		{
			if (check_time(&pr->philos[i], &finished_meals))
				return (prog);
		}
		if (finished_meals == pr->nb_philos)
			return (prog);
	}
}
