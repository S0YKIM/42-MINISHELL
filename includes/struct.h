#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char 			*data;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	char			*token;
	char			**argv;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_data
{
	t_env	*env_list;
	t_token	*token_list;
	t_ast	*astree;
}	t_data;

#endif
