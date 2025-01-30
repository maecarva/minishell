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
