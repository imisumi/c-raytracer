/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/13 14:46:01 by imisumi          ###   ########.fr       */
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
#include <math.h>

# include "../lib/cglm/build/include/cglm/cglm.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"
# include "camera.h"

#define WIDTH 1024
#define HEIGHT 512
#define ASPECT_RATIO (float)WIDTH / (float)HEIGHT
#define BPP sizeof(int32_t)
typedef vec3 ray[2];

typedef struct	s_data
{
	t_camera 	camera;
	mlx_t		*mlx;
	mlx_image_t	*image;
}				t_data;

typedef struct	s_sphere
{
	vec3		center;
	float		radius;
}				t_sphere;

void vec3_to_vec4(vec3 v, float f, vec4 dest);

// typedef struct {
// 	vec3 origin;
// 	vec3 direction;
// } ray;

#endif
