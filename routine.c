/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:43:33 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/29 22:12:23 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	start(philo->data);
	pthread_mutex_lock(&philo->r_fork);
	print_fork(philo);
	ft_usleep(philo->data, philo->data->time_to_die);
	print_dead(philo);
	pthread_mutex_unlock(&philo->r_fork);
}

void	take_fork(t_philo *philo)
{
	if (philo->philo_nb % 2)
	{
		pthread_mutex_lock(&philo->r_fork);
		print_fork(philo);
		pthread_mutex_lock(philo->l_fork);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_fork(philo);
		pthread_mutex_lock(&philo->r_fork);
		print_fork(philo);
	}
}

void	put_fork(t_philo *philo)
{
	if (philo->philo_nb % 2)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
}

void	eating(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->data->m_meal);
	philo->t_meal = get_time(philo->data);
	pthread_mutex_unlock(&philo->data->m_meal);
	print_eat(philo);
	ft_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->m_meal);
	philo->count += 1;
	pthread_mutex_unlock(&philo->data->m_meal);
	put_fork(philo);
}

void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->data->time_to_die = philo->data->time_to_die + get_time(philo->data);
	if (philo->philo_nb % 2)
		ft_usleep(philo->data, philo->data->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_stop);
		if (philo->data->stop == 1 || philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->m_stop);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->m_stop);
		eating(philo);
		print_sleep(philo);
		ft_usleep(philo->data, philo->data->time_to_sleep);
		print_think(philo);
	}
	return (0);
}
