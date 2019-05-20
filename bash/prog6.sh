#!/usr/bin/env bash

# Написать процедуру, вводящую с клавиатуры два целых числа и выводящую на экран их сумму, произведение и частное от деления первого числа на второе.

# Считываем числа
read tmp1 tmp2

# Вычисляем сумму
sum=`expr $tmp1 + $tmp2`

# Вычисляем произведение
prod=`expr $tmp1 \* $tmp2`

# Вычисляем частное
del=`expr $tmp1 \/ $tmp2`

echo "числа"
echo $tmp1
echo $tmp2

echo "Сумма"
echo $sum

echo "Произведение"
echo $prod

echo "Частное"
echo $del

exit;

avis@avis-PC[01:37:09]:~/develop/mifi/bash$ bash prog6.sh 
10 5
числа
10
5
Сумма
15
Произведение
50
Частное
2
avis@avis-PC[01:37:15]:~/develop/mifi/bash$ 
