/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/11 22:38:31 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
		mlx_put_pixel(image, x, y, color);
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

void point_at_paramater(ray r, float t, vec3 dest)
{
	vec3 tmp;
	glm_vec3_copy(r[0], dest);
	glm_vec3_copy(r[1], tmp);
	glm_vec3_scale(tmp, t, tmp);
	glm_vec3_add(dest, tmp, dest);
}

// void color(ray r,t_sphere *sphere, vec3 dest)
// {
// 	// printf("sphere[0].center = %f, %f, %f\n", sphere[0].center[0], sphere[0].center[1], sphere[0].center[2]);
// 	// printf("sphere[1].center = %f, %f, %f\n", sphere[1].center[0], sphere[1].center[1], sphere[1].center[2]);
// 	// exit(0);
	
// 	float t = hit_sphere((vec3){0.0, 0.0, -1.0}, 0.5, r);
// 	// printf("t = %f\n", t);
// 	// t = 1.0f;
// 	if (t > 0.0f)
// 	{
// 		vec3 n;
// 		point_at_paramater(r, t, n);
// 		glm_vec3_sub(n, (vec3){0.0, 0.0, -1.0}, n);
// 		glm_vec3_normalize(n);
		
// 		glm_vec3_scale((vec3){n[0] + 1.0, n[1] + 1.0, n[2] + 1.0}, 0.5, dest);
// 		return ;
// 	}

// 	vec3 unit_direction;
// 	glm_vec3_copy(r[1], unit_direction);

// 	glm_vec3_normalize(unit_direction);

// 	t = 0.5f * (unit_direction[1] + 1.0f);

// 	vec3 color1 = { 1.0, 1.0, 1.0 };
// 	vec3 color2 = { 0.5, 0.7, 1.0 };
// 	glm_vec3_scale(color1, (1.0f - t), color1);
// 	glm_vec3_scale(color2, t, color2);
// 	glm_vec3_add(color1, color2, color1);
// 	glm_vec3_copy(color1, dest);
// }

bool sphere_hit()

bool hitable_hit(ray r, float t_min, float t_max, t_hit_record rec)
{
	t_hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < 2; i++) {
		if ()
	}
}

void color(ray r,t_sphere *sphere, vec3 dest)
{
	t_hit_record rec;
	if (hitable_hit(r, 0.0f, MAXFLOAT, rec)) {
		glm_vec3_scale(rec.normal, 0.5, dest);
		return ;
	}




	
	float t = hit_sphere(sphere[0].center, 0.5, r);
	// printf("t = %f\n", t);
	// t = 1.0f;
	if (t > 0.0f)
	{
		vec3 n;
		point_at_paramater(r, t, n);
		glm_vec3_sub(n, sphere[0].center, n);
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

	t_sphere sphere[2];
	glm_vec3_copy((vec3){0.0, 0.0, -1.0}, sphere[0].center);
	sphere[0].radius = 0.5;
	glm_vec3_copy((vec3){0.0, -100.5, -1.0}, sphere[1].center);
	sphere[1].radius = 100;
	
	// t_hit_record;

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
			color(r, sphere, col);

			int ir = (255.00 * col[0]);
			int ig = (255.00 * col[1]);
			int ib = (255.00 * col[2]);
			// printf("%d %d %d\n", ir, ig, ib);
			uint32_t color = ft_pixel(ir, ig, ib, 255);
			put_pixel(data->image, x, data->image->height - y, color);
		}
	}
}

void	ft_loop_hook(void *param)
{
	t_data	*data;

	data = param;
	// hello_world(data);
	sky(data);
}

void	mlx_actions(t_data *data)
{
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
	
	mlx_actions(&data);

	mlx_loop_hook(data.mlx, ft_hook, data.mlx);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}