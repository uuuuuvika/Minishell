#include "../minishell.h"

size_t	ft_strlenn(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlenn(s1) + ft_strlenn(s2);
	join = malloc((len + 1) * sizeof(char));
	i = 0;
	if (join == 0)
		return (0);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
//	free(s1);
	return (join);
}