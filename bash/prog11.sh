#!/usr/bin/env bash

# Написать shell- процедуру, которая: осуществляет просмотр подкаталогов в текущем каталоге и выполнение команд, вводимых с терминала, до получения сигнала конец_файла или прерывание. (Сигнал прерывание действует только по окончании выполнения команды).

pwd=`pwd`

for i in *
do
    if test -d $pwd/$i
    then
        cd $pwd/$i
        while echo $i:
                trap exit 2
                read x
        do
            trap : 2; eval $x; done
        fi
    done