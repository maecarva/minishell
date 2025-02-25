/bin/env | grep "_=" ???

# TODO
leaks expand limiter

# elio
ls && ls | ls -la = fonctionne

ls -la | ls && ls = fail

cat | cat >out | grep e

cat | cat | cat | < inffeewew cat > hello | grep e


ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la | cat << stop 3
