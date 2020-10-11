#!/usr/bin/env bash

# Запуск програм через аргументы

echo $1 $2 $3 $4 $0

exit;

...
avis@avis-PC[01:01:32]:~/develop/mifi/bash$ bash prog2.sh  `date +%F` ` pwd` $HOME `whoami`
2019-05-21 /home/avis/develop/mifi/bash /home/avis avis prog2.sh
