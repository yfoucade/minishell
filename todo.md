# To fix

## heredoc

- While creating a heredoc, delimiter should not be expanded

`cat << $USER`

_in this example, the delimiter must be `$USER` and not the actual user_

## redirections

- Running : `echo "abcdef" > /dev/full`

Prints the error two times rather than one

# Unknown yet

## environment issues

- Piping minishell to minishell (from `bash`) cause first (?) instance to hang

`./minishell | ./minishell`

(pressing CTRL+C two times causes a SIGPIPE)

# To change

Uniformize error format, prefix with `minishell: ` every errors related to commands
prefix with `<command>` for every errors related to redirections