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
- [ ] Change path thing. It needs to run with `bin/ls`, check for relative and absolute paths :cat:
- [ ] Try `unset PATH` Commands with relative or absolute paths will stop working. export PATH=/bin  will allow some commands to work again  :cat:
- [ ] Set the $PATH to a multiple directory value directory1:directory2 and ensure that directories are checked in order from left to right. :cat:
- [x] Run: `''` and  `' '` fix it, it works with double quotes but not single quotes
- [ ] Test only spaces or tabs :face_with_peeking_eye:
- [x] echo -n -n -n -n hola has to print hola and no new line. Now it prints -n hola
- [x] 'ls -l'  and ls '-l'
- [x] `echo '$USER'` must print "$USER"  Now it prints $USER
- [x] expansions have to work with exported variables, this does not work with getenv()
- [x] expand whole command line
- [x] Check what happens for non existing expansions $NONEXISTING
- [ ] `'$BOB' '$JO'` should return `$BOB: command not found` :face_with_peeking_eye:

- [ ] Add data->exit _code to all builtins
- [ ] Try `$? + $?` in comparison to bash. I think it should execute only `$?` but we need to double check
- [ ] `cat $PATH`should write `no such a file or directory`

- [x] Check expansions for `cat $EXPANDTOFILE ??` Try with paths maybe?
- [ ] << EOF (without cat) is causing seg fault
- [ ] Split expansions
- [ ] Execute `$EXPANDCOMMAND` (expansions to commands)
- [x] reorganice expand function
- [ ] `cat << 'EOF'` and `cat << "EOF"`  and should not expand, maybe use a flag for what should be expanded or not :face_with_peeking_eye:
- [ ] heredoc + expansions + quotes
- [ ] Check freeing and leaks :cat:
- [ ] replace realloc (in parser) with allowed fnc
- [ ] check fucked up history :cat:

- [ ] Something goes wrong with ctrl-D and it does not aways work
- [ ] `cat '` is segfault and `cat "` does not behave like bash. Also seg fault for `echo '` `echo "` `pwd '` among others. Maybe we need to check when quotes are not pair, bash seems to wait for the second quote but maybe returnring some :non valid input error" is enough(?) :face_with_peeking_eye:
      
## general TODO:
- [ ] Simple built in commands: echo, echo -n, cd, pwd, export, unset, env, exit
- [ ] Compound commands
- [ ] < > >>  Redirections for stdin and stdout
- [ ] | output from one program to the input of the next program
- [ ] ; is used for program sequencing
- [ ] "" '' Quotes
- [ ] $PATH Environment variables
- [ ] ctrl-C, ctrl-D, ctrl-\  SIGINT, EOG, SIGQUIT
- [ ] $? should work like in bash
- [ ] Use up and down arrows to navigate through the command using termcap (mandatory) history which we will then be able to edit (at least like we can for classic lines if we feel like it (the line, not the history)).
- [ ] run programs in bg (not mandatory)
