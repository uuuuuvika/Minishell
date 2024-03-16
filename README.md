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
