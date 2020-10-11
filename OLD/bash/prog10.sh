#!/usr/bin/env bash

# Написать бесконечную процедуру, которая периодически, каждые 15 с, опрашивает систему и выводит на экран сведения о каждом вновь вошедшем в систему пользователе.

# Сохраняем текущих пользователей
who > tmp

# Убираем лишнее
cut -f1 -d" " tmp > tmp3

while true
do
    # пауза 
    # sleep 5;
    who > tmp2
    cut -f1 -d" " tmp2 > tmp4;
    for new_user in tmp4;
    do
        if grep $new_user tmp3
        then
            continue;
        else
            grep $new_user tmp2
        fi
    done
    cp tmp4 tmp3
done
