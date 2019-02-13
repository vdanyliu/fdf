/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:05:11 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/01/14 13:44:11 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_nextslashn(char *str)
{
	char *buf;

	buf = str;
	if (*buf != '\n' && *buf != '\r')
	{
		while ((*buf != '\n' && *buf != '\r') && *buf)
			buf++;
		if (*buf == '\n' || *buf == '\r')
			buf++;
	}
	else
		buf++;
	buf = ft_strdup(buf);
	free(str);
	return (buf);
}

static char		*ft_copyline(char *str)
{
	char	*buff;

	buff = str;
	if (!(*str))
		return (str);
	while ((*str != '\n' && *str != '\r') && *str)
		str++;
	return (ft_strsub(buff, 0, (str - buff)));
}

t_list static	*ft_get_fdlist(int fd, t_list *head)
{
	t_list *tmp;

	tmp = head;
	if (!head->content)
		head->content = ft_strdup("\0");
	while (tmp->next)
	{
		if ((int)tmp->next->content_size == fd)
			return (tmp->next);
		tmp = tmp->next;
	}
	tmp->next = ft_lstnew("", (size_t)fd);
	return (tmp->next);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*curr;
	int				i;
	char			buff[BUFF_SIZE + 1];
	char			*text;

	!head ? head = ft_lstnew(0, 0) : 0;
	if (fd < 0 || (read(fd, NULL, 0) < 0) || !line)
		return (-1);
	curr = ft_get_fdlist(fd, head);
	if (ft_strchr(curr->content, '\n') == 0)
		while ((i = (int)read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[i] = '\0';
			text = curr->content;
			curr->content = ft_strjoin(curr->content, buff);
			free(text);
			if (ft_strchr(buff, '\n') != 0)
				break ;
		}
	*line = ft_copyline(curr->content);
	if (ft_strlen(*line) == 0 && ft_strlen(curr->content) == 0)
		return (0);
	curr->content = ft_nextslashn(curr->content);
	return (1);
}
