#/bin/bash

case $1 in
    1)
        echo "Дано натуральное число n. Подсчитать количество цифр и нулей";
    ;;
    3)
        echo "Дана последовательность из n целых элементов. Сформировать две новых последовательности, состоящих соответственно из положительных и отрицательных элементов исходной последовательности. Элементы в результирующих последовательностях должны быть отсортированы по убыванию. Все последовательности: исходную и полученные вывести на экран.";
    ;;
    4)
        echo "Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, состоящую только из слов, начинающихся и заканчивающихся на один и тот же символ, разделенных одним пробелом. В начале строки и в конце строки не должно быть разделительных символов."
    ;;
    42)
        echo "Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку, в которой удалить из каждого слова исходной строки повторяющиеся символы. Слова в новой строке разделяются одним пробелом. В начале строки и в конце строки не должно быть разделительных символов.";
    ;;
    41)
        echo "Дана строка, содержащая слова, разделенные одним или несколькими разделительными символами (пробелами, табуляторами), в начале строки и в конце строки также могут находиться разделительные символы. Сформировать новую строку на основе исходной строки, из которой удалены слова, встречающиеся в исходной строке только один раз. Оставшиеся слова разделяются одним пробелом. В начале строки и в конце строки не должно быть разделительных символов.";
    ;;
    33)
        echo "Дана последовательность из n целых элементов. Сформировать две новых последовательности, состоящих соответственно из четных и нечетных (по значению) элементов исходной последовательности. Элементы в результирующих последовательностях должны быть отсортированы по убыванию. Все последовательности: исходную и полученные вывести на экран.";
    ;;
    *)
        echo ""
    ;;
esac

