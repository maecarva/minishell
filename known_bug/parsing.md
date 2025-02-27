/bin/env | grep "_=" ???

realloc tab double free
verif si toutes les allocs sont proteges

# TODO
leaks expand limiter, change get_file to return a linked_list OR limit file count
check every leak with funcheck

# elio
ls && ls | ls -la = fonctionne

ls -la | ls && ls = fail

cat | cat >out | grep e

cat | cat | cat | < inffeewew cat > hello | grep e


ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la | cat << stop 3


A gerer:
leaks !!
signaux !!
execute command /* || p_data->cmds[0][0] == '\0'*/ ??
export $=hallo

export hello
export                // doit affcher hello mais quand on fait env, n affiche pas 