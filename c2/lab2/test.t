#!/usr/bin/env perl

use strict;
use warnings;

use Test::More  qw| no_plan |;
use lib::abs    qw| ./lib |;

use constant {
    PATTERN     => 'hell',
    ANTIPATTERN => 'work',
    DEBUG       => $ENV{DEBUG} // 0,
};

my $prog = lib::abs::path('../build-main-Desktop-Debug/main');

open my $fh, '>', './file.txt' or die "Can't create file ./file.txt! $!";
my $text = qq(
hi
hello world
world test alarm
);
print $fh $text;
print "Исходный текст: \n$text\n" if DEBUG;
close $fh;

## Bad case: Start 

subtest "Запуск без параметров; Ожидание = вывод аргументов программы" => sub {
    my $res = cmd("$prog");
    is( $res, "usage: main -x -n pattern\n");
};

exit;

sub cmd {
    my $cmd = shift;
    warn $cmd if DEBUG;
    my $res = qx| $cmd |;
    return $res;
}
