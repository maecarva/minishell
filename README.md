# minishell

Yo ! 
J'ai trouve des trucs sur minishell.

Documentation:
  -Bash Reference Manual (GNU.org) : https://www.gnu.org/software/bash/manual/bash.html#Shell-Syntax
  -explainshell : https://explainshell.com/

explainshell c'est pour explique les commandes

BRM c'est un manual du bash.

Plan: (idee de plan)

  1-Parsing:
  
    1.a-arbre binaire: gerer les priorites de commande.
    1.b-liste chainees: tokenizer les commandes dans l'ordre de priorite.
    
  2-Exec:
  
    1-Recuperer les commandes via des listes chainees et les executer.


Idee d arbre :
typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
  type d item (cmd, pipe, ...)
  
}	t_btree;



typedef	struct s_config {
	int		argc;
	char	**argv;
	char	**environnement;
	t_btree	*tree;
	char	*current_path;
	char	*prompt;
	int		last_error_code;
}	t_config;

A free:
  environnement
  tree
  current_path
  prompt ??

valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=readline.supp ./minishell
