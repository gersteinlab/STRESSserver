#!/usr/bin/perl

##  CREDITS:
##  Author: Simon Mitternacht 2010 
##  Please Cite: 
##  Mitternacht, Simon, and Igor N. Berezovsky. "Binding leverage as a 
##  molecular basis for allosteric regulation." PLoS Comput Biol 7.9 
##  (2011): e1002148.


# Takes normal-modes from stdin and outputs the 20 first
# modes to stdout. An optional command line argument changes the
# number of modes to be output.


if (scalar @ARGV) {
    $limit = shift @ARGV;
} else {
    $limit = 20;
}
$count = 0;
while (<>) {
    ++$count if (/BEGIN/);
    last if ($count > $limit);
    print $_;
}
