# rules
- check parenthesis (quoted parenthesis, equal ( and ))
echo a && )(

# TODO
change PWD and OLDPWD when cd *OK*
leaks wildcards *OK*
wildcards **
parenthesis parsing commands
 - echo a || echo b && echo != echo a || (echo b && echo c) OK
 - ((echo a || echo aa) && echo b) OK
 - (((echo a || echo aa) && echo b) && echo c) OK
 - (((echo a || echo aa) && echo b) && echo c || echo d) OK
 - (echo a && echo b && (echo c && (echo d || echo dd))) OK
 - (echo a && echo b && (echo c )) && (echo d || echo dd)
 - (echo a && echo b && (echo c )) && (echo d || echo dd)
 - (echo a && echo b && echo c) && (echo d || echo dd)

line 188 spliter edited, add end of condition if " or ' maybe this can fuck everithing ? without this 377 test pass and with 382

# elio
ls && ls | ls -la = fonctionne

ls -la | ls && ls = fail

cat | cat >out | grep e

cat | cat | cat | < inffeewew cat > hello | grep e


ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la | cat << stop 3
