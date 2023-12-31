/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/15 17:48:25 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math.h"
#include <stdio.h>

int main(void)
{
	t_vec3 a = (t_vec3){1, 2, 3};
	t_vec3 b = (t_vec3){4, 5, 6};
	t_vec3 c = vec3_add(a, b);
	printf("%f %f %f\n", c.x, c.y, c.z);
}