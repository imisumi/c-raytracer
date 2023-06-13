/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/13 22:36:25 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include "../includes/camera.h"

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

uint32_t vec4_to_uint_color(vec4 c)
{
	uint32_t r = (uint32_t)(255.00 * c[0]);
	uint32_t g = (uint32_t)(255.00 * c[1]);
	uint32_t b = (uint32_t)(255.00 * c[2]);
	uint32_t a = (uint32_t)(255.00 * c[3]);
	return ft_pixel(r, g, b, a);
}

void ft_hook(void* param)
{
	t_data* data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void hello_world(t_data *data)
{
	//! printf image width and height
	// printf("Image width: %d\n", data->image->width);
	// printf("Image height: %d\n", data->image->height);
	for (int y = data->image->height - 1; y >= 0; y--)
	{
		for (int x = 0; x < data->image->width; x++)
		{
			float r = (float)x / (float)data->image->width;
			float g = (float)y / (float)data->image->height;
			float b = 0.2f;
			int ir = (255.00 * r);
			int ig = (255.00 * g);
			int ib = (255.00 * b);
			uint32_t color = ft_pixel(ir, ig, ib, 255);
			put_pixel(data->image, x, data->image->height - y, color);
		}
	}
}

float hit_sphere(vec3 center, float radius, ray r)
{
	vec3 oc;
	glm_vec3_copy(r[0], oc);
	glm_vec3_sub(oc, center, oc);
	float a = glm_vec3_dot(r[1], r[1]);
	float b = 2.0f * glm_vec3_dot(oc, r[1]);
	float c = glm_vec3_dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0f);
	else
		return (-b - sqrt(discriminant)) / (2.0f * a);
}

void vec3_min_value(float *v, float value)
{
	if (v[0] < value)
		v[0] = value;
	if (v[1] < value)
		v[1] = value;
	if (v[2] < value)
		v[2] = value;
}

void point_at_paramater(ray r, float t, vec3 dest)
{
	vec3 tmp;
	glm_vec3_copy(r[0], dest);
	glm_vec3_copy(r[1], tmp);
	glm_vec3_scale(tmp, t, tmp);
	glm_vec3_add(dest, tmp, dest);
}

void vec3_to_vec4(vec3 v, float f, vec4 dest)
{
	dest[0] = v[0];
	dest[1] = v[1];
	dest[2] = v[2];
	dest[3] = f;
}

void color(ray r, vec3 dest)
{
	float t = hit_sphere((vec3){0.0, 0.0, -1.0}, 0.5, r);
	// printf("t = %f\n", t);
	// t = 1.0f;
	if (t > 0.0f)
	{
		vec3 n;
		point_at_paramater(r, t, n);
		glm_vec3_sub(n, (vec3){0.0, 0.0, -1.0}, n);
		glm_vec3_normalize(n);
		
		glm_vec3_scale((vec3){n[0] + 1.0, n[1] + 1.0, n[2] + 1.0}, 0.5, dest);
		return ;
	}

	vec3 unit_direction;
	glm_vec3_copy(r[1], unit_direction);

	glm_vec3_normalize(unit_direction);

	t = 0.5f * (unit_direction[1] + 1.0f);

	vec3 color1 = { 1.0, 1.0, 1.0 };
	vec3 color2 = { 0.5, 0.7, 1.0 };
	glm_vec3_scale(color1, (1.0f - t), color1);
	glm_vec3_scale(color2, t, color2);
	glm_vec3_add(color1, color2, color1);
	glm_vec3_copy(color1, dest);
}

void sky(t_data *data)
{
	vec3 lower_left_corner = { -2.0, -1.0, -1.0 };
	vec3 horizontal = { 4.0, 0.0, 0.0 };
	vec3 vertical = { 0.0, 2.0, 0.0 };
	vec3 origin = { 0.0, 0.0, 0.0 };
	for (int y = data->image->height - 1; y >= 0; y--)
	{
		for (int x = 0; x < data->image->width; x++)
		{
			float u = (float)x / (float)data->image->width;
			float v = (float)y / (float)data->image->height;

			ray r;
			vec3 temp;
			glm_vec3_copy(origin, r[0]);

			glm_vec3_copy(lower_left_corner, r[1]);

			glm_vec3_scale(horizontal, u, temp);
			glm_vec3_add(r[1], temp, r[1]);
			
			glm_vec3_scale(vertical, v, temp);
			glm_vec3_add(r[1], temp, r[1]);
			
			vec3 col;
			color(r, col);

			int ir = (255.00 * col[0]);
			int ig = (255.00 * col[1]);
			int ib = (255.00 * col[2]);
			// printf("%d %d %d\n", ir, ig, ib);
			uint32_t color = ft_pixel(ir, ig, ib, 255);
			put_pixel(data->image, x, data->image->height - y, color);
		}
	}
}

void trace_ray(ray ray, vec4 color)
{
	vec3 ray_origin;
	vec3 ray_direction;
	
	// vec3 ray_origin = {0.0f, 0.0f, 1.0f};
	// vec3 ray_direction = { coord[0] * ASPECT_RATIO, coord[1], -1.0 };

	glm_vec3_copy(ray[0], ray_origin);
	glm_vec3_copy(ray[1], ray_direction);

	float radius = 0.5f;
	// glm_vec3_normalize(ray_direction);

	

	// TODO (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
	//? a = ray origin
	//? b = ray direction
	//? r = radius
	//? t = time
	float a = glm_vec3_dot(ray_direction, ray_direction);
	float b = 2.0f * glm_vec3_dot(ray_origin, ray_direction);
	float c = glm_vec3_dot(ray_origin, ray_origin) - (radius * radius);

	// TODO Quadratic formula discriminant:
	// TODO b^2 - 4ac


	float discriminant = (b * b) - (4.0f * a * c);
	if (discriminant < 0.0f) {
		glm_vec4_copy((vec4){.1, .1, .1, 1}, color);
		return ;
	}
	
	// TODO (-b +- sqrt(discriminant)) / (2.0f * a)
	float t0 = (-b + sqrtf(discriminant)) / (2.0f * a);
	float closest_t = (-b - sqrtf(discriminant)) / (2.0f * a);

	vec3 hitpoint;
	glm_vec3_scale(ray_direction, closest_t, hitpoint);
	glm_vec3_add(ray_origin, hitpoint, hitpoint);
	vec3 normal;
	glm_vec3_copy(hitpoint, normal);
	glm_vec3_normalize(normal);

	vec3 light_direction = {-1.0f, -1.0f, -1.0f};
	glm_vec3_normalize(light_direction);
	glm_vec3_scale(light_direction, -1.0f, light_direction); //! == cos(anlge)
	float d = glm_vec3_dot(normal, light_direction);
	vec3_min_value(normal, 0.0f);

	vec3 sphere_color = {1.0f, 0.0f, 1.0f};
	// glm_vec3_copy(normal, sphere_color);
	// glm_vec3_scale(sphere_color, 0.5f, sphere_color);
	// glm_vec3_adds(sphere_color, 0.5f, sphere_color);
	vec3_to_vec4(sphere_color, 1.0f, color);

	glm_vec3_scale(color, d, color);

	return ;
}

void render(t_data *data)
{
	vec3 ray_origin;
	glm_vec3_copy(data->camera.m_position, ray_origin);
	vec3 ray_direction;
	ray ray;
	glm_vec3_copy(ray_origin, ray[0]);
	for (int y = data->image->height - 1; y >= 0; y--)
	{
		for (int x = 0; x < data->image->width; x++)
		{
			// vec2 coord;
			// coord[0] = (float)x / (float)data->image->width;
			// coord[1] = (float)y / (float)data->image->height;
			// //! from 0 -> 1 to -1 -> 1
			// glm_vec2_scale(coord, 2.0, coord);
			// glm_vec2_sub(coord, (vec2){1.0, 1.0}, coord);
			glm_vec3_copy(data->camera.ray_direction[x + y * data->image->width], ray_direction);
			
			glm_vec3_copy(ray_direction, ray[1]);
			
			vec4 color = {0.0f, 0.0f, 0.0f, 1.0f};
			trace_ray(ray, color);
			glm_vec4_clamp(color, 0.0f, 1.0f);
			// printf("%f %f %f %f\n", color[0], color[1], color[2], color[3]);
			put_pixel(data->image, x, data->image->height - y, vec4_to_uint_color(color));
		}
	}
}

void create_camera(t_data *d, float vertical_fov, float near_clip, float far_clip)
{
	d->camera.m_vertical_fov = vertical_fov;
	d->camera.m_near_clip = near_clip;
	d->camera.m_far_clip = far_clip;
	glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, d->camera.m_forward_direction);
	glm_vec3_copy((vec3){0.0f, 0.0f, 3.0f}, d->camera.m_position);
}

// void on_update(t_data *d)
// {
	
// }

void	ft_loop_hook(void *param)
{
	t_data	*data;

	data = param;
	on_update(data);
	// sky(data);
	render(data);
	// hello_world(data);
}

void	mlx_actions(t_data *data)
{
	create_camera(data, 45.0f, 0.1f, 100.0f);
	recalculate_view(data);
	recalculate_projection(data);
	recalculate_ray_direction(data);
	
	mlx_loop_hook(data->mlx, ft_loop_hook, data);
	mlx_loop_hook(data->mlx, ft_hook, data);

	mlx_loop(data->mlx);

	mlx_terminate(data->mlx);
	exit(EXIT_SUCCESS);
}

int main(int argc, const char* argv[])
{
	t_data data;

	// Gotta error check this stuff
	data.mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracer", false);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.image)
	{
		mlx_close_window(data.mlx);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		exit(EXIT_FAILURE);
	}
	
	init_camera(&data);
	mlx_actions(&data);

	mlx_loop_hook(data.mlx, ft_hook, data.mlx);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}