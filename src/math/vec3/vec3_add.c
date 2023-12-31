/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/15 17:51:51 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/math.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	vec3_add_float(t_vec3 a, float f)
{
	t_vec3	res;

	res.x = a.x + f;
	res.y = a.y + f;
	res.z = a.z + f;
	return (res);
}
