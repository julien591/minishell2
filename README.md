# minishell2

A shell in C who handles:
- simple command (eg: ls -l)
- builtins: cd, env, setenv, unsetenv, exit
- Redirections: '<' '<<' '>' '>>'
- Pipe and multipipes (eg: ls -l | cat -e | wc)
- Separators (eg: touch toto; ls > toto; cat toto)
