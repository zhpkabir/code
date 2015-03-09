#!/usr/bin/env perl

@array=qw(this is perl scrpt);
$format="This iter are:\n".("%10s\n"x@array);
printf $format, @array;
printf "This iter are:\n".("%10s\n"x@array), @array;
