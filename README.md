# Minishell

## simulate linux [environment](https://gist.github.com/CarloCattano/73482a9e846e27165e85dcf32cda91ad) on mac :

to build
```
docker build -t ubuntu .
```

to run it
```
docker run -it -v $(pwd):/home/root ubuntu
```

## TODO:

[ ] Simple built in commands: echo, echo -n, cd, pwd, export, unset, env, exit
[ ] Compound commands
[ ] < > >>  Redirections for stdin and stdout
[ ] | output from one program to the input of the next program
[ ] ; is used for program sequencing
[ ] "" '' Quotes
[ ] $PATH Environment variables
[ ] ctrl-C, ctrl-D, ctrl-\  SIGINT, EOG, SIGQUIT
[ ] $? should work like in bash
[ ] Use up and down arrows to navigate through the command using termcap (mandatory) history which we will then be able to edit
[ ] (at least like we can for classic lines if we feel like it (the line, not the history).

[ ] & run programs in bg (not mandatory)

[ ] Built in commands
[ ]  echo
[ ]  echo -n
[ ]  cd
[ ]  pwd
[ ]  export
[ ]  unset
[ ]  env
[ ]  exit
