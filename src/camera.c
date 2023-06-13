/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/13 14:46:36 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/camera.h"
#include "../includes/main.h"

void mat4_set_value(float *m, float v)
{
	int i;

	i = 0;
	while (i < 16)
	{
		m[i] = v;
		i++;
	}
}

void vec3_set_value(float *m, float v)
{
	int i;

	i = 0;
	while (i < 3)
	{
		m[i] = v;
		i++;
	}
}

void mat4_add_mat4(float *m1, float *m2, float v)
{
	int i;

	i = 0;
	while (i < 16)
	{
		m1[i] = m2[i];
		i++;
	}
}

void init_camera(t_data *d)
{
	// glm_mat4_identity((float *)d->camera.m_projection);
	// glm_mat4_identity((float *)d->camera.m_view);
	// glm_mat4_identity((float *)d->camera.m_inv_projection);
	// glm_mat4_identity((float *)d->camera.m_inv_view);
	glm_mat4_identity(d->camera.m_projection);
	glm_mat4_identity(d->camera.m_view);
	glm_mat4_identity(d->camera.m_inv_projection);
	glm_mat4_identity(d->camera.m_inv_view);

	
	d->camera.m_vertical_fov = 45.0f;
	d->camera.m_near_clip = 0.1f;
	d->camera.m_far_clip = 100.0f;

	d->camera.ray_direction = malloc(sizeof(vec3) * WIDTH * HEIGHT);

	vec3_set_value((float *)d->camera.m_position, 0.0f);
	vec3_set_value((float *)d->camera.m_forward_direction, 0.0f);

	
}
void recalculate_projection(t_data *d)
{
	float rad = glm_rad(d->camera.m_vertical_fov);
	glm_perspective(rad, ASPECT_RATIO, d->camera.m_near_clip, d->camera.m_far_clip, d->camera.m_projection);
	glm_mat4_inv(d->camera.m_projection, d->camera.m_inv_projection);
	// mat4 t;
	// glm_mat4_mul(d->camera.m_projection, d->camera.m_inv_projection, t);
	// printf("t: %f %f %f %f\n", t[0][0], t[0][1], t[0][2], t[0][3]);
	// printf("t: %f %f %f %f\n", t[1][0], t[1][1], t[1][2], t[1][3]);
	// printf("t: %f %f %f %f\n", t[2][0], t[2][1], t[2][2], t[2][3]);
	// printf("t: %f %f %f %f\n", t[3][0], t[3][1], t[3][2], t[3][3]);
}

void recalculate_view(t_data *d)
{
	vec3 temp;
	glm_vec3_add(d->camera.m_position, d->camera.m_forward_direction, temp);
	glm_lookat(d->camera.m_position, temp, (vec3){0.0f, 1.0f, 0.0f}, d->camera.m_view);
	glm_mat4_inv(d->camera.m_view, d->camera.m_inv_view);
	// mat4 t;
	// glm_mat4_mul(d->camera.m_view, d->camera.m_inv_view, t);
	// printf("t: %f %f %f %f\n", t[0][0], t[0][1], t[0][2], t[0][3]);
	// printf("t: %f %f %f %f\n", t[1][0], t[1][1], t[1][2], t[1][3]);
	// printf("t: %f %f %f %f\n", t[2][0], t[2][1], t[2][2], t[2][3]);
	// printf("t: %f %f %f %f\n", t[3][0], t[3][1], t[3][2], t[3][3]);
	
}

void vec4_to_vec3(float *v4, float *v3)
{
	v3[0] = v4[0];
	v3[1] = v4[1];
	v3[2] = v4[2];
}

// void vec3_to_vec4(float *v3, float *v4, float value)
// {
// 	v4[0] = v3[0];
// 	v4[1] = v3[1];
// 	v4[2] = v3[2];
// 	v4[3] = value;
// }

void recalculate_ray_direction(t_data *d)
{
	for (int y = d->image->height - 1; y >= 0; y--)
	{
		for (int x = 0; x < d->image->width; x++)
		{
			vec2 coord;
			coord[0] = (float)x / (float)d->image->width;
			coord[1] = (float)y / (float)d->image->height;
			//! from 0 -> 1 to -1 -> 1
			glm_vec2_scale(coord, 2.0, coord);
			glm_vec2_sub(coord, (vec2){1.0, 1.0}, coord);
			
			vec4 target;
			glm_mat4_mulv(d->camera.m_inv_projection, (vec4){coord[0], coord[1], 1.0f, 1.0f}, target);
			glm_vec4_normalize(target);
			vec3 tmp;
			vec4 temp;
			vec4_to_vec3(target, tmp);
			glm_vec3_scale(tmp, target[3], tmp);
			glm_vec3_normalize(tmp);
			// vec3_to_vec4(tmp, temp, 0.0f);
			vec3_to_vec4(tmp, 0.0f, temp);
			glm_mat4_mulv(d->camera.m_inv_view, temp, temp);
			vec3 ray_dir;
			vec4_to_vec3(temp, ray_dir);
			d->camera.ray_direction[y * d->image->width + x][0] = ray_dir[0];
			d->camera.ray_direction[y * d->image->width + x][1] = ray_dir[1];
			d->camera.ray_direction[y * d->image->width + x][2] = ray_dir[2];
		}
	}
}

void on_update(t_data *d)
{
	bool moved = false;
	vec3 temp;
	vec3 up_direction = {0.0f, 1.0f, 0.0f};
	d->camera.m_forward_direction[0] = 0.0f;
	d->camera.m_forward_direction[1] = 0.0f;
	d->camera.m_forward_direction[2] = -1.0f;
	vec3 right_direction;
	glm_vec3_cross(d->camera.m_forward_direction, up_direction, right_direction);

	float speed = 0.5f;

	if (!mlx_is_mouse_down(d->mlx, MLX_MOUSE_BUTTON_RIGHT))
		return ;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W)) {
		glm_vec3_scale(d->camera.m_forward_direction, speed, temp);
		glm_vec3_add(d->camera.m_position, temp, d->camera.m_position);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S)) {
		glm_vec3_scale(d->camera.m_forward_direction, speed, temp);
		glm_vec3_sub(d->camera.m_position, temp, d->camera.m_position);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A)) {
		glm_vec3_scale(right_direction, speed, temp);
		glm_vec3_sub(d->camera.m_position, temp, d->camera.m_position);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D)) {
		glm_vec3_scale(right_direction, speed, temp);
		glm_vec3_add(d->camera.m_position, temp, d->camera.m_position);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_Q)) {
		glm_vec3_scale(up_direction, speed, temp);
		glm_vec3_sub(d->camera.m_position, temp, d->camera.m_position);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_E)) {
		glm_vec3_scale(up_direction, speed, temp);
		glm_vec3_add(d->camera.m_position, temp, d->camera.m_position);
		moved = true;
	}

	// TODO: rotation

	moved = true;
	if (moved) {
		recalculate_view(d);
		recalculate_projection(d);
		recalculate_ray_direction(d);
	}
	printf("camera position: %f, %f, %f\n", d->camera.m_position[0], d->camera.m_position[1], d->camera.m_position[2]);
}
