#!/usr/bin/env perl

chomp($line = <STDIN>);
if ($line eq ""){
	print "Please Enter a number or string\n";
}
else{
	print "That line of input is:$line\n";
}
