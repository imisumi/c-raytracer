/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/11 20:54:09 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITABLE_H
# define HITABLE_H

#include "main.h"

typedef struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
} t_hit_record;

#endif