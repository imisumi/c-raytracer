/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/15 17:52:41 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/math.h"

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec3	vec3_sub_float(t_vec3 a, float f)
{
	t_vec3	res;

	res.x = a.x - f;
	res.y = a.y - f;
	res.z = a.z - f;
	return (res);
}
