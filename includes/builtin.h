#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

/*
 * Builtin Functions
*/
int		ft_env(char **cmds, t_data *data);
int		ft_pwd(void);
int		ft_export(char **cmds, t_data *data);
int		ft_cd(char **cmds, t_data *data);
int		ft_unset(char **cmds, t_data *data);
void	ft_exit(t_ast *ast, t_data *data);
int		ft_echo(t_ast *ast);


/*
 * Util Functions
*/
int		is_valid_key_name(char *key);
int		is_str_num(char *str);
int		is_str_long_long(char *str);

#endif
