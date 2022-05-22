# things to keep in mind:

# start of executor info:
Executor needs to not do anything if args[0] == "exit"
check in main if the only command is "exit" (with spaces before or after is fine), only then should minishell exit.

in and out fds are set to -2 to indicate "no redirections", only if they are not -2 was there a redirection that needs to overwrite a potential pipe. -1 is already used as error return value from open(). executor should only use in or out if they are >= 0. 

sleep 1 | sleep 1 | sleep 1 | sleep 2 | sleep 1 | sleep 1 | echo test
# end of executor info

Save the PATH env variable into data struct before every  - beware of leaks. That's important because a user could unset PATH in between.

Handle the redirections outside of the executor.
The executor will only dup2 the fdin and fdout into STDIN and STDOUT and execve.

Handle all the heredocs before doing anything else. save the content of the heredoc as one string in the char *file of redirection list.

Error management handled in a clean way from the beginning on.

./no_permissions_file
-> Permission denied
no_permissions_file
-> command not found

< fi"le1" cat
tokenizer sees input redirection up until metacharacter. then it handles the next thing as no redirection, no pipe - so it has to be a command.
< fi"le1 c"at
tokenizer doesn't interpret the spacebar as metacharacter, so it thinks the cat is still part of the input redirection "file1 cat".

echo test > out ec>out2 ho more
-> writes to out2 file "test ec ho more" - you can have more words to your command after redirections up until you start a new command with a pipe.

echo a"b'c'd'e"<br>
-> ab'c'd'e<br><br>
echo a'b"c"d"e'<br>
-> ab"c"d"e<br>
so it when it encounters one kind of quote, it will not interpret any special character until it reaches another of the same quotes.<br><br>
$test "$testvar" '$novar' | "$var $var '$var" $novar '$novar' | "$exp" ||| "$exp"<br>
-> expands will look something like:<br>
i: 0    010<br>
i: 1    11100<br>
i: 2    1<br>
i: 3    (empty string)<br>
i: 4    (empty string)<br>
i: 5    1<br><br>

<!-- Tokenizer:
breaks a stream of text into tokens, usually looking for whitespaces (maybe also metacharacters). -->

Lexer:
basically tokenizer, but usually attaches extra context to the tokens (this is a number or string literal or equality operator or ...).

Expander
echo "$abc"'$def'
-> first one expands, second one doesn't. but they are part of the same argv

Parser:
makes sense of the tokens, uses them for further decisions.
Joins all WORD tokens up until end of tokens or until PIPE (end of command) into an array of strings to be used by the executor later.
!!!after lexer, go through tokens once to combine redirs:<br>
if there is a redir token, check if next exists and is of type word. if not, throw e.g.: "syntax error near unexpected token '>'". if it's fine, free old redir token's content, put next token's content into redir's content, remove the next token and link the rest of the linked list accordingly.

# readline:

If you want the user to be able to get at the line later, (with C-p for example), you must call add_history() to save the line away in a history list of such lines.

Here is a function which usefully replaces the standard gets() library function, and has the advantage of no static buffer to overflow:
/* A static variable for holding the line. */
static char *line_read = (char *)NULL;

/* Read a string, and return a pointer to it.
   Returns NULL on EOF. */
char *
rl_gets ()
{
  /* If the buffer has already been allocated,
     return the memory to the free pool. */
  if (line_read)
    {
      free (line_read);
      line_read = (char *)NULL;
    }

  /* Get a line from the user. */
  line_read = readline ("");

  /* If the line has any text in it,
     save it on the history. */
  if (line_read && *line_read)
    add_history (line_read);

  return (line_read);
}

# interesting behaviour for bonus
((( echo test ||echo 123))||echo a2)<br>
bash: ((: echo test ||echo 123: syntax error in expression (error token is "test ||echo 123")<br>
a2<br>
