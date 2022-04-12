#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

/*
 * Builtin Functions
*/
int		ft_env(t_data *data);
int		ft_pwd(void);
int		ft_export(char **cmds, t_data *data);
int		ft_cd(char **cmds, t_data *data);

/*
 * Util Functions
*/
int		is_valid_key_name(char *key);
int		print_error_msg(char **cmds);

#endif
