/*
** builtin.h for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/include
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 14:40:15 2016 julien
** Last update Fri May 06 14:40:27 2016 julien
*/

#ifndef		BUILTIN_H_
# define	BUILTIN_H_

int	test_builtin(t_envi *instuctions, char *s);
void	builtin_env(char **env);
void	setenv_unsetenv(t_envi *instuctions);
void	builtin_cd(t_envi *instuctionsh, int nb_arg);
void	cd_home(char **env, char *home);

#endif /* !BUILTIN_H_ */
