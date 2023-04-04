#include "../header/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
    int index = 0;
	while (s1[index] && s2[index])
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

void	two_dim_free(char **str)
{
	int i;

	i = 0;
	if(!str)
		return ;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	two_dim_len(char **str)
{
	int i;

	i = 0;
	if(!str)
		return (0);
	while(str[i])
		i++;
	return (i);
}
