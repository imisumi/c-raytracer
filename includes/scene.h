/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/14 15:38:19 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "main.h"

typedef struct s_material
{
	vec3 albedo;
	float roughness;
	float metallic;
}	t_material;

typedef struct s_sphere
{
	vec3 position;
	float radius;

	// t_material material;
	int material_index;
	// vec3 albedo;
}	t_sphere;

typedef struct s_scene
{
	int number_of_spheres;
	t_sphere *spheres;
	t_material materials[10];
}	t_scene;

#endif