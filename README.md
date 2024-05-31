# Minishell

## simulate linux [environment](https://gist.github.com/CarloCattano/73482a9e846e27165e85dcf32cda91ad) on mac :

to build
```
docker build -t ubuntu .
```

to run it
```
docker run -it -v $(pwd):/home/root ubuntu

apt-get install git build-essential libreadline-dev
```

## To fix for Evaluation Sheet:
- [x] Change path thing. It needs to run with `bin/ls`, check for relative and absolute paths
- [x] Try `unset PATH` Commands with relative or absolute paths will stop working. export PATH=/bin  will allow some commands to work again
- [x] Set the $PATH to a multiple directory value directory1:directory2 and ensure that directories are checked in order from left to right.
---
- [x] Run: `''` and  `' '` fix it, it works with double quotes but not single quotes
- [x] Test only spaces or tabs
- [x] echo -n -n -n -n hola has to print hola and no new line. Now it prints -n hola
- [x] 'ls -l'  and ls '-l'
- [x] `echo '$USER'` must print "$USER"  Now it prints $USER
- [x] expansions have to work with exported variables, this does not work with getenv()
- [x] expand whole command line
- [x] Check what happens for non existing expansions $NONEXISTING
- [x] `'$BOB' '$JO'` should return `$BOB: command not found` :face_with_peeking_eye:
- [x] `cat '` is segfault and `cat "` does not behave like bash. Also seg fault for `echo '` `echo "` `pwd '` among others.
- [x] `cat << 'EOF'` and `cat << "EOF"`  and should not expand, maybe use a flag for what should be expanded or not
- [ ] heredoc + expansions + quotes :face_with_peeking_eye:
---
- [ ] Add data->exit _code to all builtins
- [ ] Try `$? + $?` in comparison to bash. I think it should execute only `$?` but we need to double check
- [x] `cat $PATH`should write `no such a file or directory`
---
- [x] Check expansions for `cat $EXPANDTOFILE ??` Try with paths maybe?
- [x] Reorganice expand function
- [ ] Split expansions so we can store commands in env and expand them after
- [ ] Execute `$EXPANDCOMMAND` (expansions to commands)
- [ ] echo "$TERM fsfsfs" substitude "$TERM fsfsfs" by "\0" but it should print $TERM fsfsfs
---
- [ ] replace realloc (in parser) with allowed fnc
- [ ] check fucked up history :cat:
- [ ] Something goes wrong with ctrl-D and it does not aways work
- [ ] cat '$TERM' giving seg fault when not forking ( cat '$TERM' | wc is fine)
- [ ] << EOF (without cat) is causing seg fault
- [ ] Check freeing and leaks :cat:
      
## General TODO:
- [x] Simple built in commands: echo, echo -n, cd, pwd, export, unset, env, exit
- [ ] Compound commands
- [x] < > >>  Redirections for stdin and stdout
- [x] | output from one program to the input of the next program
- [ ] ; is used for program sequencing
- [ ] "" '' Quotes
- [x] $PATH Environment variables
- [ ] ctrl-C, ctrl-D, ctrl-\  SIGINT, EOG, SIGQUIT
- [x] $? should work like in bash
- [ ] Use up and down arrows to navigate through the command using termcap (mandatory) history which we will then be able to edit (at least like we can for classic lines if we feel like it (the line, not the history)).
- [ ] run programs in bg (not mandatory)
