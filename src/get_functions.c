/*
** get_functions.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:54:01 2016 julien
** Last update Fri May 06 10:54:02 2016 julien
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"str.h"
#include	"token.h"

int	my_getnbr(char *str)
{
  int i;
  int nbr;
  int negatif;

  i = 0;
  nbr = 0;
  negatif = 0;
  while (str[i] != '\0')
    {
      while (str[i] < '0' || str[i] > '9')
	{
	  if (str[i] == '-')
	    negatif++;
	  i++;
	}
      while (str[i] >= '0' && str[i] <= '9')
	{
	  nbr = ((nbr * 10) + (str[i] - 48));
	  i++;
	}
    }
  if (negatif % 2 != 0)
    nbr = -nbr;
  return (nbr);
}

char	*my_getenv(char **env)
{
  int	i;
  int	j;
  int	k;
  int	cmp;
  char	*ret;

  i = 0;
  j = 5;
  k = 0;
  cmp = 1;
  while (env[i] != NULL && ((cmp = my_strcmp(env[i], "PATH")) != 0))
    i++;
  if (cmp != 0)
    return (NULL);
  ret = my_malloc(sizeof(char) * (my_strlen(env[i])));
  while (env[i][j] != '\0')
    {
      ret[k] = env[i][j];
      j++;
      k++;
    }
  ret[k] = '\0';
  return (ret);
}

char	*my_gethome(char **env)
{
  int	i;
  int	j;
  int	k;
  char	*ret;

  i = 0;
  j = 5;
  k = 1;
  while (env[i] != NULL && (k = my_strcmp(env[i], "HOME")) != 0)
    i++;
  if (k != 0)
    return (NULL);
  k = 0;
  ret = my_malloc(sizeof(char) * my_strlen(env[i]));
  while (env[i][j] != '\0')
    {
      ret[k] = env[i][j];
      j++;
      k++;
    }
  ret[k] = '\0';
  return (ret);
}

char	*my_get_old_pwd(char **env)
{
  int	i;
  int	j;
  int	k;
  char	*ret;

  i = 0;
  j = 7;
  k = 1;
  while (env[i] != NULL && (k = my_strcmp(env[i], "OLDPWD")) != 0)
    i++;
  if (k != 0)
    return (NULL);
  k = 0;
  ret = my_malloc(sizeof(char) * my_strlen(env[i]));
  while (env[i][j] != '\0')
    {
      ret[k] = env[i][j];
      j++;
      k++;
    }
  ret[k] = '\0';
  return (ret);
}
