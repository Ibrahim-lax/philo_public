/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:21:24 by librahim          #+#    #+#             */
/*   Updated: 2024/12/09 23:56:26 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int    gettime()
{
    struct timeval  t;
    long int        r;

    gettimeofday(&t, NULL);
    r = t.tv_sec * 1000000 + t.tv_usec;
    return (r);
}
