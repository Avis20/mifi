

# Прерывания

* Аппаратные
* Програмные

Кольцевой - 

int N

int 21h - Прерывания Dos-а
21 - номер прерывания
```
mov ah, 09h
lea dx, str ; или mov dx, offset str
int 21h
```
! В конце строки - символ доллара 

`str db 'Hello world$'`

buf [255]       [255]
    ожидаемое   введенное

```
buf db 255
str_len db ?
len db 255 dub(?)
mov ah, 0Ah ;  
lea dx, buf
int 21h
```

```
lea si, buf
inc si
mov len, [si]
inc si
```

## Открытие 
   
```
mov ah, 3Dh
mov al,     ; 0 - чтение, 1 - запись, 2 - чтение/запись
lea dx, file_name
int 21h

```

```
file_name db 'Hello'

```

## Закрытие файла

```
mov ah, 3eh
mov bx, handle
int 21h;

```

## Чтение 

```
mov ah, 3fh
mov bx, handle
mov cx, number  ; кол-во байт сколько прочитать
lea dx, buffers
mov 21h         
```

## Запись

```
mov ah, 40h
mov bx, handle
mov cx, numbers
lea dx, buffers; - имя файла?!

```

## Что?

```
mov ah, 42h     ; смещение указателя
mov bx, handle 
mov al,     0 - от начала файла, 1 - текущее положение(?), 2 - с  конца файла
mov cx:dx - помещается смещение 
mov 21h
```
в carry flag - ошибка

Дескриптор - указатель на память

### Стандартные дескрипторы 
* 0 - stdin
* 1 - stdout
* 2 - stderror
* 3 - stdlpt

> то число которое вернулось записываем в CX



