# rules
- check parenthesis (quoted parenthesis, equal ( and ))
echo a && )(

# TODO
change PWD and OLDPWD when cd *OK*
leaks wildcards *OK*
parenthesis parsing

# elio
ls && ls | ls -la = fonctionne

ls -la | ls && ls = fail

cat | cat >out | grep e

cat | cat | cat | < inffeewew cat > hello | grep e