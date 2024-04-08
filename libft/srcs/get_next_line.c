/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:33:49 by zyeoh             #+#    #+#             */
/*   Updated: 2023/12/11 16:00:12 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_custom_strjoin(char *full_str, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(full_str, buffer);
	free(full_str);
	return (temp);
}

char	*read_file(int fd, char *full_str)
{
	char	*buffer;
	int		byte_size;

	if (!full_str)
	{
		full_str = (char *)malloc(sizeof(char));
		*full_str = '\0';
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	byte_size = 1;
	while (!ft_strchr(full_str, '\n') && byte_size > 0)
	{
		byte_size = read(fd, buffer, BUFFER_SIZE);
		if (byte_size == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_size] = '\0';
		full_str = ft_custom_strjoin(full_str, buffer);
	}
	free(buffer);
	return (full_str);
}

char	*get_line(char *full_str)
{
	char	*temp;
	int		len;

	if (!*full_str)
		return (NULL);
	len = -1;
	while (full_str[++len] && full_str[len] != '\n')
		;
	temp = ft_substr(full_str, 0, len + 1);
	if (!temp)
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

char	*next_line(char *full_str)
{
	char	*temp;
	char	*start;

	start = ft_strchr(full_str, '\n');
	if (!start)
	{
		free(full_str);
		return (NULL);
	}
	temp = ft_substr(start + 1, 0, ft_strlen(start + 1));
	free(full_str);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*full_str[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	full_str[fd] = read_file(fd, full_str[fd]);
	if (!full_str[fd])
	{
		free(full_str[fd]);
		return (NULL);
	}
	line = get_line(full_str[fd]);
	full_str[fd] = next_line(full_str[fd]);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*raw;
	int		n;

	n = -1;
	while (++n < 6)
	{
		fd = open("test.txt", O_RDONLY);
		raw = get_next_line(fd);
		printf("%s\n", raw);
	}
	free(raw);
	close(fd);
}


int	main(void)
{
	char	*line;
	int		i;
	int		fd3;

	// int fd1;
	// int fd2;
	// fd1 = open("tests/test.txt", O_RDONLY);
	// fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 100)
	{
		// line = get_next_line(fd1);
		// printf("line [%02d]: %s\n", i, line);
		// free(line);
		// line = get_next_line(fd2);
		// printf("line [%02d]: %s\n", i, line);
		// free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		i++;
	}
	// close(fd1);
	// close(fd2);
	close(fd3);
	return (0);
}
*/