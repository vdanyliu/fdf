/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:25:57 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/02/22 14:26:24 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_free_split(char **str)
{
	char **buff;

	buff = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(buff);
}

void	fdf_free(t_map_lines *leak)
{
	if (leak == NULL)
		return ;
	while (leak->next != NULL)
	{
		leak = leak->next;
		free(leak->prev->map_chars);
		free(leak->prev);
	}
	free(leak->map_chars);
	free(leak);
}
