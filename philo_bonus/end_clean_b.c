/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_clean_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:22:46 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/18 16:09:25 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	close_sems(t_data_b *data)
{
	int i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		sem_close(data->forks[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		sem_unlink(data->name_tab[i]);
		i++;
	}
	sem_close(data->lock);
	sem_unlink("/lock");
	//free(data->sems);
}

void	free_data_b(t_data_b *data)
{
	free(data->tv);
	free(data);
}

