/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/18 08:29:53 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	in_solutions(t_array *sol, int node)
{
	int i;

	i = 0;
	while (i < (int)sol->size)
	{
		if (ARRAY_DATA(sol, i) == node)
			return (1);
		i++;
	}
	return (0);
}

static int	get_min_path(int **routetab, int size, int row, int end)
{
	int col;
	int min;
	int node;

	col = 0;
	min = size + 1;
	node = size;
	while (col < size)
	{
		if (routetab[row][col] == 1 &&
			routetab[end][col] < min)
		{
			min = routetab[end][col];
			node = col;
		}
		col++;
	}
	return (node);
}

/*
** Does not tolerate any intersections
*/

int			path_finder_1(int ***routetab, int size, t_array *sol, int end)
{
	int node;
	int	temp;

	node = get_min_path(*routetab, size, ARRAY_DATA(sol, sol->size - 1), end);
	if (node == end)
		return (fta_append(sol, &node, 1) || 1);
	while (node < size && (*routetab)[end][node] < size + 1 &&
		!in_solutions(sol, node))
	{
		fta_append(sol, &node, 1);
		temp = (*routetab)[end][node];
		(*routetab)[end][node] = size + 1;
		if (path_finder_1(routetab, size, sol, end))
			return (1);
		fta_popback(sol, 1);
		node = get_min_path(*routetab, size,
				ARRAY_DATA(sol, sol->size - 1), end);
	}
	return (0);
}
