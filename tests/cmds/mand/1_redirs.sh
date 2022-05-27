### PERMISSION DENIED ###
touch tmp_redir_out_file1
chmod -r tmp_redir_out_file1
/bin/echo 1 > tmp_redir_out tmp_redir_out_file1

/bin/grep 1 < inputfile

/bin/grep 1 < NO_SUCH_FILE

/bin/grep 1 < inputfile < inputfile

/bin/grep 1 < NO_SUCH_FILE < inputfile

> tmp_std_outfile && echo 1

rm -f tmp_std_outfile

>tmp_std_outfile && ls | grep tmp_std_outfile

rm -f tmp_std_outfile

"" >tmp_std_outfile && ls | grep tmp_std_outfile

rm -f tmp_std_outfile

/bin/echo 1 >/dev/null | /usr/bin/grep 1

/bin/echo 1 >/dev/null | /bin/echo 2

/bin/echo >/dev/null 1 | /usr/bin/grep 1

/bin/echo >/dev/null 1 | /bin/echo 2

### HERE_DOC ###
cat << lim
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

<<lim cat
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

cat << lim
test
lim

cat << EOF
"EOF"
!! HELLO
@42 !!
 EOF\t\b\n
testing your minishell :)
limm
EOF

cat << hello
$USER
$NOVAR
$HOME
hello

cat << 'lim'
$USER
$NOVAR
$HOME
lim

cat << lim''
$USER
$NOVAR
$HOME
lim

cat << ''lim
$USER
$NOVAR
$HOME
lim

cat << 'lim'
$USER
$NOVAR
$HOME
lim
