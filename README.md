# Minishell

## simullate linux enviroment on mac:

to build
```
docker build -t ubuntu .
```

to run it
```
docker run -it -v $(pwd):/home/root ubuntu
```
