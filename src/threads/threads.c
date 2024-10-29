/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:31:26 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/29 16:01:12 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	threads(t_program *pr)
{
	size_t		i;
	pthread_t	observer;

	i = 0;
	/*if (pthread_create(&observer, NULL, &controler, (void *)pr) != 0)
		return ;*/
	if (pr->nb_philos == 1)
		pthread_create()
	while (i < pr->nb_philos)
	{
		if (pthread_create(&pr->philos[i].thread, NULL, &routine,
				(void *)&pr->philos[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	pthread_join(observer, NULL);
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
