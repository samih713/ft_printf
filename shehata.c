
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 42

char	*get_next_line(int fd)
{
	static char		*line;
	static size_t	index;
	char			*buffer;
	char			*print_out;
	size_t			buf_size;
	size_t			index_2;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf_size = (size_t)BUFFER_SIZE;
	buffer = malloc(sizeof(char) * (buf_size));
	if (!buffer)
		return (0);
	if (!line)
	{
		line = malloc(1);
		index = 0;
	}
	while (!ft_strchr(buffer, '\n'))
	{
		read(fd, buffer, buf_size);
		line = ft_strjoin(line, buffer);
	}
	index_2 = find_endingpoint(line, index);
	print_out = ft_substr(line, index, (index_2 - index));
	index = index_2;
	return (print_out);
}



