#!/usr/bin/env bash

# Написать процедуру, вводящую в начало файла_1 некоторый текст с клавиатуры, затем присоединяющего содержимое файла_2, затем снова вводящего текст с клавиатуры в конецфайла_1. Имена файлов передаются в процедуру в качестве параметров.

cat - $1 > tmp
cat tmp $2 > $1

exit;

avis@avis-PC[01:23:51]:~/develop/mifi/bash$ cat f1 
test
avis@avis-PC[01:23:56]:~/develop/mifi/bash$ cat f2 
alarm
avis@avis-PC[01:23:59]:~/develop/mifi/bash$ bash prog4.sh f1 f2
eee
avis@avis-PC[01:24:04]:~/develop/mifi/bash$ cat f1 
eee
test
alarm


т.е в f1 в начале то что ввел пользователь, потом f1 + f2