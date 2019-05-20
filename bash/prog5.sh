#!/usr/bin/env bash

# Написать процедуру, находящую в файле, имя которого передается в качестве параметра, все строки, содержащие вводимую с клавиатуры во время работы процедуры последовательность символов.

read tmp        # Считываем строку
grep $tmp $1    # Ищем строку в файле $1

exit;

avis@avis-PC[01:27:11]:~/develop/mifi/bash$ cat f1 
dsa
wq
eee
test
alarm
alarm
avis@avis-PC[01:28:14]:~/develop/mifi/bash$ bash prog5.sh f1
test
test
avis@avis-PC[01:28:27]:~/develop/mifi/bash$ bash prog5.sh f1
dsa
dsa
avis@avis-PC[01:28:33]:~/develop/mifi/bash$ bash prog5.sh f1
w
wq
avis@avis-PC[01:28:34]:~/develop/mifi/bash$ bash prog5.sh f1
r
alarm
alarm
avis@avis-PC[01:28:37]:~/develop/mifi/bash$ bash prog5.sh f1
1
avis@avis-PC[01:28:41]:~/develop/mifi/bash$ 
