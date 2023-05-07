/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyilmaz <emyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:47 by emyilmaz          #+#    #+#             */
/*   Updated: 2023/05/04 11:44:49 by emyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*nlfinder(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	str = calloc(sizeof(char), (i + 2));
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

static char	*afternl(char *s)
{
	int		i;
	int		j;
	char	*abc;

	i = 0;
	j = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		free (s);
		return (NULL);
	}
	abc = calloc(sizeof(char), (ft_strlen(s) - i));
	if (!abc)
		return (NULL);
	i++;
	while (s[i] != '\0')
		abc[j++] = s[i++];
	free (s);
	return (abc);
}

char	*get_next_line(int fd)
{
	static char	*schar;
	char		*s;
	char		*tempchar;
	int			textsize;

	textsize = 1;
	s = calloc(sizeof(char), BUFFER_SIZE + 1);
	while (!ft_strchr(schar, '\n') && textsize != 0)
	{
		textsize = read(fd, s, BUFFER_SIZE);
		if (textsize == -1)
		{
			free (s);
			return (NULL);
		}
		s[textsize] = '\0';
		schar = ft_strjoin(schar, s);
	}
	tempchar = nlfinder(schar);
	schar = afternl(schar);
	free(s);
	return (tempchar);
}
/*#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd1 = open("t1.txt", O_RDONLY);
	int fd2 = open("t2.txt", O_RDONLY);
	int fd3 = open("t3.txt", O_RDONLY);

	char	*line1 = get_next_line(fd1);
	char	*line2 = get_next_line(fd2);
	char	*line3 = get_next_line(fd3);

	while (*line1 || *line2 || *line3)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		printf("%s", line1);
		printf("%s", line2);
		printf("%s", line3);

		fd1 = open("t1.txt", O_RDONLY);
		fd2 = open("t2.txt", O_RDONLY);
		fd3 = open("t3.txt", O_RDONLY);
	}

}*/
