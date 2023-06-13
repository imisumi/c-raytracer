/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/14 00:01:06 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

# include "../lib/cglm/build/include/cglm/cglm.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"
# include "camera.h"
# include "scene.h"

#define WIDTH 1200
#define HEIGHT 848
#define ASPECT_RATIO (float)WIDTH / (float)HEIGHT
#define BPP sizeof(int32_t)
typedef vec3 ray[2];

typedef struct	s_data
{
	t_camera 	camera;
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*image;
}				t_data;

// typedef struct	s_sphere
// {
// 	vec3		center;
// 	float		radius;
// }				t_sphere;

void thread_ray_direction(t_data *d);

void vec3_to_vec4(vec3 v, float f, vec4 dest);

// typedef struct {
// 	vec3 origin;
// 	vec3 direction;
// } ray;

#endif
