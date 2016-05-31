/*
** read.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:55:00 2016 julien
** Last update Thu May 26 18:40:54 2016 Julien Leleu
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"str.h"

int		just_space(char *str, int i)
{
  int		space;

  space = 1;
  while (str[i] != '\0')
    {
      if (str[i] != ' ' && str[i] != '\t')
	space = 0;
      i++;
    }
  return (space);
}

int		just_comma(char *str)
{
  int		comma;
  int		i;

  comma = 1;
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] != ' ' && str[i] != ';' && str[i] != '\t')
	comma = 0;
      i++;
    }
  return (comma);
}

char		*del_space(char *str)
{
  char		*ret;
  int		i;
  int		j;

  i = 0;
  j = 0;
  ret = my_malloc(sizeof(char) * (my_strlen(str) + 1));
  while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
      i++;
  while (i != my_strlen(str) && just_space(str, i) == 0)
    {
      if ((str[i] == ' ' || str[i] == '\t') && (str[i + 1] != '\0'))
	{
	  ret[j++] = ' ';
	  while ((str[i] == ' ' || str[i] == '\t') && (str[i + 1] != '\0'))
	    i++;
	}
      ret[j++] = str[i++];
    }
  free(str);
  ret[j] = '\0';
  return (ret);
}

char		*my_read()
{
  char		buf[4096];
  char		*s;
  int		nb;
  int		i;

  i = 0;
  nb = read(0, buf, 4096);
  if (nb < 0)
    return (NULL);
  if (nb == 0)
    {
      my_putstr("exit\n");
      exit(0);
    }
  s = my_malloc(sizeof(char) * nb);
  while (i < nb - 1)
    {
      s[i] = buf[i];
      i++;
    }
  s[i] = '\0';
  return (s);
}
