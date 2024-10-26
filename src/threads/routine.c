/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:42:02 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/26 18:29:46 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	phwrite(char *str, size_t time, int id, t_philos *ph)
{
	pthread_mutex_lock(ph->write_lock);
	printf(str, time, id);
	pthread_mutex_unlock(ph->write_lock);
}

static int	eat(t_philos *ph)
{
	size_t	time;

	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(ph->left_fork);
	time = get_current_time() - ph->start_time;
	if (is_dead_flag(ph))
		return (1);
	if (*ph->max_meals == ph->current_meals)
	{
		set_dead_flag(1, ph);
		dead_write(ph);
		return (1);
	}
	else
		phwrite("%zu %d is eating\n", time, ph->id, ph);
	pthread_mutex_lock(ph->meals_lock);
	ph->current_meals++;
	ph->time_lmeal = get_current_time() - ph->start_time;
	pthread_mutex_unlock(ph->meals_lock);
	ft_usleep(*ph->time_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	return (0);
}

static int	think(t_philos *ph)
{
	size_t	time;

	time = get_current_time() - ph->start_time;
	if (is_dead_flag(ph))
		return (1);	
	else
		phwrite("%zu %d is thinking\n", time, ph->id, ph);
	if (time - ph->time_lmeal >= *ph->time_die)
	{
		set_dead_flag(1, ph);
		dead_write(ph);
		return (1);
	}
	return (0);
}

static int	phsleep(t_philos *ph)
{
	size_t	time;

	time = get_current_time() - ph->start_time;
	if (is_dead_flag(ph))
		return (1);
	if (time - ph->time_lmeal >= *ph->time_die)
	{
		set_dead_flag(1, ph);
		dead_write(ph);
		return (1);	
	}
	else
		phwrite("%zu %d is sleeping\n", time, ph->id, ph);
	ft_usleep(*ph->time_sleep);
	time = get_current_time() - ph->start_time;
	if  (time - ph->time_lmeal > *ph->time_die)
	{
		set_dead_flag(1, ph);
		dead_write(ph);
		return (1);	
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philos	*ph;

	ph = (t_philos *)philo;
	while (true)
	{
		if (!is_dead_flag(ph))
		{
			if (!eat(ph))
			{
				if (!phsleep(ph))
				{
					if (!think(ph))
						continue;
				}
			}
		}
		set_dead_flag(1, ph);
		return (NULL);
	}
	return (NULL);
}

/*
		if (is_dead_flag(ph))
		{
			dead_write(ph);
			return (NULL);
		}
		if (eat(philo))
		{
			dead_write(ph);
			return (NULL);
		}
		if (Psleep(philo))
		{
			dead_write(ph);
			return (NULL);
		}
		if (think(philo))
		{
			dead_write(ph);
			return (NULL);
		}
*/
