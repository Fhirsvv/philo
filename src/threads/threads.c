/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:31:26 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/29 16:09:02 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	*one_philo(void *philo)
{
	t_philos *ph;

	ph = (t_philos *)philo;
	phwrite("%zu %d has taken a fork\n", time, ph);
	ft_usleep(ph->time_die);
	dead_write(ph);
	return (NULL);
}

void	threads(t_program *pr)
{
	size_t		i;
	pthread_t	one_philo;

	i = 0;
	if (pr->nb_philos == 1)
		pthread_create(&one_philo, NULL, &one_philo, (void *)&pr->philos[0]);
	while (i < pr->nb_philos)
	{
		if (pthread_create(&pr->philos[i].thread, NULL, &routine,
				(void *)&pr->philos[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < pr->nb_philos)
	{
		pthread_join(pr->philos[i].thread, NULL);
		i++;
	}
}

void	set_dead_flag(int i, t_philos *ph)
{
	pthread_mutex_lock(ph->dead_lock);
	*ph->dead_flag = i;
	pthread_mutex_unlock(ph->dead_lock);
}

int	is_dead_flag(t_philos *ph)
{
	int	i;

	pthread_mutex_lock(ph->dead_lock);
	i = *ph->dead_flag;
	pthread_mutex_unlock(ph->dead_lock);
	return (i);
}
