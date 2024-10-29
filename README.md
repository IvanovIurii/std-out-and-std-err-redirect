# Redirect child process outputs

## Описание

Утилита запускающая, другую программу, переданную ей в качестве аргумента.
Стандартный вывод запускаемой программы перенаправлен в файл out.txt, стандартный поток ошибок - в файл err.txt.

### Как запускать

```
g++ -std=c++17 -o output_redirect main.cpp && ./output_redirect <executable with arguments>
```

### Примеры

```
./output_redirect /sbin/ping ya.ru
./output_redirect /bin/ls -l -a -р
./output_redirect /usr/bin/top
```