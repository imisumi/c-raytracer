/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/14 18:06:44 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/camera.h"
#include "../includes/main.h"

int frames = 0;

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
	glm_mat4_identity(d->camera.m_projection);
	glm_mat4_identity(d->camera.m_view);
	glm_mat4_identity(d->camera.m_inv_projection);
	glm_mat4_identity(d->camera.m_inv_view);

	
	d->camera.m_vertical_fov = 45.0f;
	d->camera.m_near_clip = 0.1f;
	d->camera.m_far_clip = 100.0f;

	d->camera.ray_direction = malloc(sizeof(vec3) * WIDTH * HEIGHT);
	d->camera.accumulation_data = malloc(sizeof(vec4) * WIDTH * HEIGHT);
	d->camera.frame_index = 1;
	d->camera.settings.accumulate = true;

	vec3_set_value((float *)d->camera.m_position, 0.0f);
	vec3_set_value((float *)d->camera.m_forward_direction, 0.0f);

	d->camera.mouse_delta[0] = 0.0f;
	d->camera.mouse_delta[1] = 0.0f;
}

void recalculate_projection(t_data *d)
{
	float rad = glm_rad(d->camera.m_vertical_fov);
	glm_perspective(rad, ASPECT_RATIO, d->camera.m_near_clip, d->camera.m_far_clip, d->camera.m_projection);
	glm_mat4_inv(d->camera.m_projection, d->camera.m_inv_projection);
	
	// printf("projection: %f %f %f %f\n", d->camera.m_projection[0][0], d->camera.m_projection[0][1], d->camera.m_projection[0][2], d->camera.m_projection[0][3]);
	// printf("inv_projection: %f %f %f %f\n", d->camera.m_inv_projection[1][0], d->camera.m_inv_projection[1][1], d->camera.m_inv_projection[1][2], d->camera.m_inv_projection[1][3]);
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
void recalculate_ray_direction(t_data *d)
{
	int yy = 0;
	int height = d->image->height;
	int width = d->image->width;
	vec2 coord;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			coord[0] = (float)x / (float)width;
			coord[1] = (float)y / (float)height;
			//! from 0 -> 1 to -1 -> 1
			glm_vec2_scale(coord, 2.0, coord);
			glm_vec2_sub(coord, (vec2){1.0f, 1.0f}, coord);
			// printf("check\n");
			
			vec4 target;
			glm_mat4_mulv(d->camera.m_inv_projection, (vec4){coord[0], coord[1], 1.0f, 1.0f}, target);

			vec3 tmp;
			vec4 temp;
			vec4_to_vec3(target, tmp);

			glm_vec3_divs(tmp, target[3], tmp);
			glm_vec3_normalize(tmp);

			vec3_to_vec4(tmp, 0.0f, temp);
			
			glm_mat4_mulv(d->camera.m_inv_view, temp, temp);

			vec4_to_vec3(temp, d->camera.ray_direction[yy * width + x]);
		}
		yy++;
	}
}

void quat_angle_axis(float angle, float *axis, float *quat)
{
	float a = angle;
	float s = sinf(a * 0.5f);
	float c = cosf(a * 0.5f);

	quat[0] = axis[0] * s;
	quat[1] = axis[1] * s;
	quat[2] = axis[2] * s;
	quat[3] = c;
}


void quat_cross(float *q1, float *q2, float *dest)
{
	dest[3] = q1[3] * q2[3] - q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2];
	dest[0] = q1[3] * q2[0] + q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1];
	dest[1] = q1[3] * q2[1] + q1[1] * q2[3] + q1[2] * q2[0] - q1[0] * q2[2];
	dest[2] = q1[3] * q2[2] + q1[2] * q2[3] + q1[0] * q2[1] - q1[1] * q2[0];

	// dest[3] = q1[3] * q2[3] - q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2];
	// dest[0] = q1[3] * q2[0] + q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1];
	// dest[1] = q1[3] * q2[1] + q1[1] * q2[3] + q1[2] * q2[0] - q1[0] * q2[2];
	// dest[2] = q1[3] * q2[2] + q1[2] * q2[3] + q1[0] * q2[1] - q1[1] * q2[0];
	
}
				// q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
				// q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y
				// q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z
				// q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x




void on_update(t_data *d)
{
	printf("%d\n", frames);
	frames++;
	bool moved = false;
	bool rotated = false;
	vec3 temp;
	vec3 up_direction = {0.0f, 1.0f, 0.0f};
	// d->camera.m_forward_direction[0] = 0.0f;
	// d->camera.m_forward_direction[1] = 0.0f;
	// d->camera.m_forward_direction[2] = -1.0f;
	vec3 right_direction;
	glm_vec3_cross(d->camera.m_forward_direction, up_direction, right_direction);

	float speed = 0.25f;

	if (!mlx_is_mouse_down(d->mlx, MLX_MOUSE_BUTTON_RIGHT))
		return ;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W)) {
		glm_vec3_scale(d->camera.m_forward_direction, speed, temp);
		glm_vec3_add(d->camera.m_position, temp, d->camera.m_position);
		// printf("camera: %f %f %f\n", d->camera.m_position[0], d->camera.m_position[1], d->camera.m_position[2]);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S)) {
		glm_vec3_scale(d->camera.m_forward_direction, speed, temp);
		glm_vec3_sub(d->camera.m_position, temp, d->camera.m_position);
		// printf
		moved = true;
	}
	// d->camera.m_position[0] += 0.05f;
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
	if (mlx_is_key_down(d->mlx, MLX_KEY_UP)) {
		d->camera.mouse_delta[1] += 10.0f;
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_DOWN)) {
		d->camera.mouse_delta[1] -= 10.0f;
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT)) {
		d->camera.mouse_delta[0] -= 10.0f;
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT)) {
		d->camera.mouse_delta[0] += 10.0f;
		moved = true;
	}

	if (d->camera.mouse_delta[0] != 0 || d->camera.mouse_delta[1] != 0) {
		float pitch_delta = d->camera.mouse_delta[1] * 0.01f;
		float yaw_delta = d->camera.mouse_delta[0] * 0.01f;
		versor q;
		versor temp1;
		versor temp2;
		// printf("%f\n\n", -pitch_delta);
		quat_angle_axis(-pitch_delta, right_direction, temp1);
		// printf("temp1: %f, %f, %f, %f\n\n", temp1[3], temp1[0], temp1[1], temp1[2]);
		
		quat_angle_axis(-yaw_delta, (vec3){0.0f, 1.0f, 0.0f}, temp2);
		// printf("temp2: %f, %f, %f, %f\n\n", temp2[3], temp2[0], temp2[1], temp2[2]);
	
		quat_cross(temp1, temp2, q);
		// printf("q: %f, %f, %f, %f\n\n", q[3], q[0], q[1], q[2]);
	
		glm_quat_normalize(q);
		// printf("q: %f, %f, %f, %f\n\n", q[3], q[0], q[1], q[2]);
		glm_quat_rotatev(q, d->camera.m_forward_direction, d->camera.m_forward_direction);
		// printf("forward: %f, %f, %f\n\n", d->camera.m_forward_direction[0], d->camera.m_forward_direction[1], d->camera.m_forward_direction[2]);
		d->camera.mouse_delta[0] = 0.0f;
		d->camera.mouse_delta[1] = 0.0f;
		moved = true;
		rotated = true;
	}

	if (moved) {
		d->camera.frame_index = 1;
		recalculate_view(d);
		if (rotated) {
			recalculate_ray_direction(d);
		}
		// recalculate_projection(d);
		// printf("camera position: %f, %f, %f\n", d->camera.m_position[0], d->camera.m_position[1], d->camera.m_position[2]);
	}

}
