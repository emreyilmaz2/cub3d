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

int check_directions(char **str)
{
    int i = 0;

    while(i < 4)
    {
        printf("%s\n", str[i]);
        if(!ft_strcmp(str[i], "NO") || !ft_strcmp(str[i], "SO") || !ft_strcmp(str[i], "WE") || !ft_strcmp(str[i], "EA"))
        {
            printf("esit\n");
            return(0);
        }
        i++;
    }
    printf("check the directions");
    exit(1);
}