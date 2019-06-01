#!/usr/bin/env bash

# Написать процедуру, которая:
# 1. среди пользователей, работающих в данный момент времени в системе, находит всех пользователей, имена которых содержатся во вводимой в процедуру символьной строке;
# 2. выводит на экран найденные имена пользователей.

# Формируем файл с пользователями
who > tmp

# Вводим имя
read name

# Уст. переменную name как аргументы (?)
set $name

while [ "$1" ]
do
    grep $1 tmp
    shift
done