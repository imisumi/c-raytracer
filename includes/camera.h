/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/13 22:36:20 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "main.h"

typedef struct s_data t_data;

typedef struct	s_camera
{
	mat4 m_projection;
	mat4 m_view;
	mat4 m_inv_projection;
	mat4 m_inv_view;

	float m_vertical_fov;
	float m_near_clip;
	float m_far_clip;

	vec3 *ray_direction;
	vec2 mouse_delta;

	vec3 m_position;
	vec3 m_forward_direction;
}				t_camera;

void init_camera(t_data *d);
void on_update(t_data *d);

void recalculate_view(t_data *d);
void recalculate_projection(t_data *d);
void recalculate_ray_direction(t_data *d);



#endif