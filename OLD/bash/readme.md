# Welcome


1. Что будет выведено на экран после выполнения следующего протокола по обработке обычных файлов?

```
$ ls
f1  f2  f3
$ [ -f f1 ]; echo $? > view
$ [ -f f2 ]; echo $? > view
$ [ -f f3 ]; echo $? > view
$ cat view
```

Ответ: 0

2. Что будет выведено на экран после выполнения следующего протокола по обработке обычных файлов?

```
$ ls
f1  f2  f4
$ [ -f f1 ]; echo $? > view
$ [ -f f2 ]; echo $? > view
$ [ -f f3 ]; echo $? > view
$ cat view

```

Ответ: 1

3. Что будет выведено на экран после выполнения следующего протокола?

```
$ a1=001
$ a2=002
$ export a2
$ bash
$ a1=101; a2=102
$ echo a1=$a1 a2=$a2
```

Ответ: a1=101 a2=102

4. Какие из перечисленных команд можно использовать для управления процессами

    * kill
    * fg
    * bg

Ответ: kill (?)

5. Какие параметры будут выведены на экран после выполнения следующего протокола:

```
$ set vara varb varc vard vare varf varf varg varh
$ shift # (сдвиг вправо)
$ echo $1 $2 $3
```

Ответ: varb varc vard

6. Что будет на экране после выполнения следующей процедуры?

```
$ vara=varb+1; varb=varc+2; varc=3
$ echo vara+var+varc
```

Ответ: vara+var+varc

7. Какое из перечисленных свойств являются свойствами встроенного редактора vi UNIX ?
    * Создание новых пустых файлов
    * Поиск строк файла по фрагментам текста
    * Отмена всех результатов редактирования
    * Независимость от вида терминала
    * Использование в качестве команд клавиш любой алфавитно-цифровой клавиатуры
    * Наличие специального буфера памяти для размещения редактируемого файла
    * Наличие специальных режимов редактирования:Режим команд, режим ввода текста в файл, режим обработки группы строк или целого файла
    * При программировании процедур могут использоваться команды командного интерфейса UNIX
    * При программировании процедур могут использоваться операторы Shell
    * shell-процедуры обрабатываются интерпретатором Shell

8. Что будет на экране после выполнения следующей процедуры

```
b=$(w=abcde; expr $w : '.*')
echo b>f; cat f
```

Ответ: b

9. Что будет результатом выполнения следующего протокола?

```
$ var1=001
$ var2=002
$ export var2
$ bash
$ exit
$ var1=101,var2=102
$ echo "var1=$var1 var2=$var2"
```

Ответ: var1=101,var2=102 var2=002

10. Что будет на экране после выполнения следующего протокола?

```
$ var1=001
$ var2=002
$ export var2
$ bash
$ echo "v1=$var1 v2=$var2"
$ var1=101,var2=102
$ echo "v1=$var1 v2=$var2"
```

Ответ: v1=101,var2=102 v2=002

11. Что будет на экране после выполнения следующего протокола?

```
$ var1=001
$ var2=002
$ export var1
$ bash
$ var1=101,var2=102
$ exit
$ echo "v1=$var1 v2=$var2"
```

Ответ: v1=001 v2=002

12. Что будет на экране после выполнения следующего протокола?

```
$ var1=001
$ var2=002
$ export var2
$ bash
$ var1=101,var2=102
$ echo "v1=$var1 v2=$var2"
```

Ответ: v1=101,var2=102 v2=002

13. Что будет на экране после выполнения следующего протокола?

```
$ ls
fa fb fc fd
$ ls | read f1 f2
$ echo $f2 $f3
```

Ответ: ничего не будет

14. Что будет на экране после выполнения следующего протокола?

```
$ echo ‘`ls`’
```

Ответ: `ls`

15. Что будет на экране после выполнения следующего протокола?

```
$ echo ‘ls’
```

Ответ: Листинг текущего каталога

16. Сколько раз будет выполнено тело цикла в следующей shell-процедуре?

```
echo a b c > file
cat 'cat file'
while ["$2"]
do
    shift
done
```

Ответ: 2 (?)

17. Сколько раз будет выполнено тело цикла в следующей shell-процедуре?

```
echo a b c > file
set `cat file`
while ["$1"]
do
    shift
done
```

Ответ: 3 (?)

18. Сколько раз будет выполнено тело цикла в следующей shell-процедуре?

```
for a in 1 2 3aa
do
    echo $a
done
```

Ответ: 3

19. Сколько раз будет выполнено тело цикла в следующей shell-процедуре?

```
echo a b c > file
set `cat file`
until [ '$3' = '' ]
do 
    shift 
done
```

Ответ: 1 (?)

20. Сколько раз будет выполнено тело цикла в следующей shell-процедуре?

```
for p in
do
    echo $P
done
```
Ответ: 0 (?)

21. Сколько раз будет выполнено тело цикла в следующей shell-процедуре?

```
i=1
until [ $i -ge 5 ]
do
    i='expr $i + 1'
done
```
Ответ: 0 (?)

22. Сколько раз будет выполнено тело цикла в следующей shell-процедуре?

```
i=1
while [ $i -lt 5 ]
do
    echo $i;
    i=`expr $i + 1`;
done
```
Ответ: 4

23. Что из перечисленного можно исползовать, для того чтобы прекратить последнюю фоновую задачу?

Ответ:  
    * Команду fg, а затем CTRL-C
    * `kill %%`

24. Какую команду нужно применить для прекрощения выполнения программы(процесс PID=1234)?
Ответ:
    * kill 1234
    * kill -TERM 1234
    * kill -s KILL 1234
    * kill -9 1234

25. Что нужно предпринять, чтобы выйти из бесконечного цикла?

```
while true
do
    read p
    if test $p -le 05
        then exit
    fi
done
```

Ответ:
    * ввести с клавиатуры цифру 5
    * ввести с клавиатуры число 05
    * ввести с клавиатуры любую цифру, меньшую 5 
    * нажать комбинацию клавиш CTRL-C

26. Что нужно предпринять, чтобы выйти из бесконечного цикла?

```
while true
do
    read p
    if [$p -eq 05]
        then exit
    fi
done
```

Ответ:
    * ввести с клавиатуры цифру 5
    * ввести с клавиатуры число 05
    * нажать комбинацию клавиш CTRL-C

27. Каким процессам доступны локальные переменные родительского процесса для чтения и переопределения?

Ответ: Собственному процессу

28. Какое действие выполняются следующей командной строкой?

```
$ nohup proc >rez &
```

Ответ: (?)
    * Процедура запускается в фоновом режиме с блокировкой прерываний с клавиатуры
    * Результаты процедуры перенаправляются вместо экрана в указанный файл

29. Каким процессам доступны глобальные переменные родительского процесса для чтения и переопределения? 
Ответ:
    * Собственному процессу
    * Порожденным процессам(дочерним)
    * Процессам-внукам

30. Какое действие выполняются следующей командной строкой?

```
$ nohup prog &
```

Ответ:
    * Процедура prog запускается на исполнение в фоновом режиме
    * Для процедуры proc прерывания с клавиатуры заблокированы
    * Результаты процедуры выводятся в специальный системный файл

31. Какие действия выполняются следующей строкой

```
$ laba3 > filea
```
Ответ: ввод игнорируется (?)

32. Что будет на экране консоли после выполнения следующей процедуры?

```
if true; echo $? >fil;[-f fil]
then cat fil
else echo fil
fi
```
Ответ: 0

33. Что будет на экране консоли после выполнения следующей процедуры?

```
if false; echo $? >fil; [ -f fil ]
    then cat fil
    else echo fil
fi
```

Ответ: 1

34. Что будет на экране консоли после выполнения следующей процедуры?

```
if cd,echo $? >fil,[-f fil]
then cat fil
else echo fil
fi
```
Ответ: 0

35. Что будет на экране после выполнения следующей процедуры?

```
a=6,b=5,c=3
v=`expr $a+$b+$c`
echo v
```
Ответ: v

36. Что будет на экране после выполнения следующей процедуры?

```
v=ls
echo a=$v
```
Ответ: a=ls

37. Что будет на экране после выполнения следующей процедуры?

```
a=6; b=5; c=3
v=`expr $a + $b + $c`
echo $v
```
Ответ: 14

38. Что будет на экране после выполнения следующей процедуры?

```
a=6;b=5;c=3
echo $a+$b+$c
```
Ответ: 6 + 5 + 3

39. Что будет на экране после выполнения следующей процедуры?

```
x=3; y=5
z=`expr $x \<= $y`
echo $z > n
cat n
```
Ответ: 1

40. Что будет на экране после выполнения следующей процедуры?

```
x=3;y=3
z=`expr $x \< $y`
echo $z > n
cat n
```
Ответ: 0

41. Что будет на экране после выполнения следующей процедуры?

```
x=123; [ 0123 = $x ]; echo $?
```
Ответ: 1

42. Что будет на экране после выполнения следующей процедуры?

```
x=345
test $x -eq 0345
echo $?
```
Ответ: 0

43. Что будет на экране после выполнения следующей процедуры?

```
p=$(a=1; b=2; expr $a + $b)
echo $p
```
Ответ: 3

44. Что будет на экране после выполнения следующей процедуры?

```
p=$(v=ab; expr $v : .\(.*\).)
echo $p
```
Ответ: b (?)

45. Что будет на экране после выполнения следующей процедуры?

```
p=$(v=abcde; expr $v : '.\(.*\).')
echo $p
```
Ответ: bcd

46. Что будет на экране после выполнения следующей процедуры?

```
v=$(a=4; b=3; expr $a \* $b)
echo $v
```
Ответ: 12

47. Что будет на экране после выполнения следующей процедуры?

```
v=$(a=4; expr $a / 2; expr $a \* 3)
echo v
```
Ответ: v

48. Что будет на экране после выполнения следующей процедуры?

```
a=b+1; b=c+2; c=3
echo a+b+c
```
Ответ: a+b+c

49. Что будет на экране после выполнения следующей процедуры?

```
a=b+1; b=c+2; c=3
echo $a+$b+$c
```
Ответ: b+1+c+2+3


50. Что будет на экране после выполнения следующей процедуры?

```
a=b+1; b=c+2; c=3
v='`expr $a+$b+$c`'
echo $v
```
Ответ: 'expr $a+$b+$c'

51. Что будет на экране после выполнения следующего протокола по обработке обычных файлов?

```
$ ls
f1 f2 d3 d4
$ [ -f f1 ]; echo $? > rez
$ [ -f f2 ]; echo $? >>rez
$ [ -f f3 ]; echo $? >>rez
cat rez
```
Ответ: 0 0 1

52. Что будет на экране после выполнения следующего протокола по обработке обычных файлов f1,f2 и каталогов d3,d4?

```
ls
# f1 f2 d3 d4
[ -d f1 ]; echo $? > r
[ -f f2 ]; echo $? > r
[ -d f3 ]; echo $? > r
[ -d f3 ]; echo $? > r
cat r
```

Ответ: 1

53. Что будет на экране после выполнения следующего протокола по обработке обычных файлов?

```
ls
# f1 f2 f4
[ -d f1 ]; echo $? >    rez
[ -f f2 ]; echo $? >>   rez
[ -d d3 ]; echo $? >>   rez
[ -d d4 ]; echo $? >    rez
cat rez
```

Ответ: 0

54. Что будет на экране после выполнения следующего протокола по обработке обычных файлов?

```
ls
fila filb filc fild
ls | read f1 f2 f4
echo $f1 $f3
```

Ответ: fila filc fild


55. Что будет на экране после выполнения следующего протокола по обработке обычных файлов?

```
ls
# fila filb filc fild
ls | read f2 f3
echo $f2 $f3
```
Ответ: fila filb filc fild

56. Что будет на экране после выполнения следующего протокола по обработке обычных файлов?

```
ls
# fila filb filc fild
ls | read f1
echo $f1
```

Ответ: fila filb filc fild

57. Что будет на экране после выполнения следующего протокола?

```
ls
a b c d
ls | read f1 f2 f3
echo $f1 $f3
```

Ответ: a c d

58. Что будет на экране после выполнения следующего протокола?

```
ls
# f1 f2 f3
for var in *
do
    echo $var
done
```
Ответ: f1 f2 f3

59. Что будет на экране после выполнения следующего протокола?

```
ls
# f1 f2 f3
set `ls`
for var
do
    echo $var
done
```

Ответ: тексты файлов f1 f2 f3

60. Что будет на экране после выполнения следующего протокола?

```
ls
# f1 f2 f3
set `ls`
for var
do
    echo var
done
```
Ответ: var var var

61. Что будет на экране после выполнения следующего протокола?

```
$ echo $HOME
/home/user/lev
$ v=$HOME; cd $v; echo $v
```

Ответ: /home/user/lev

62. Что будет на экране после выполнения следующего протокола?

```
$ echo $HOME
/home/user/lev
```

Ответ: /home/user/lev

63. Какие параметры будут выведены на экран следующего протокола?

```
set a b c d aa bb cc dd
shift
echo $1 $2 $3
```
Ответ: b c d