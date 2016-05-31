/*
** token.h for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/include
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 14:41:08 2016 julien
** Last update Thu May 26 18:29:29 2016 Julien Leleu
*/

#ifndef		TOKEN_H_
# define	TOKEN_H_

int		is_right_chevron(char *str);
void		right_chevron(char *s, t_envi *instuctions, int code);
int		is_comma(char *str);
void		comma(char *s, t_envi *instuctions);
int		is_left_chevron(char *str);
int		left_redir(char *bin, char **cmd, char **env, char *file);
void		left_chevron(char *s, t_envi *instuctions);
int		is_pipe(char *str);
void		init_pipe(char *s, t_envi *instuctions);
void		double_left_chevron(char *s, t_envi *instuctions);
char		*get_path_pipe(char **path, char *s);
int		nb_pipes(char *str);
t_envi		*my_triple_array(char **cut, t_envi *instuctions);
char		***set_commands(t_envi *instuctions, char ***command);

#endif /* !TOKEN_H_ */
