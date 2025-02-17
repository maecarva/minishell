# rules
- check parenthesis (quoted parenthesis, equal ( and ))


# TODO
change PWD and OLDPWD when cd 
leaks wildcards

# elio
ls && ls | ls -la = fonctionne

ls -la | ls && ls = fail

cat | cat >out | grep e
