#!/usr/bin/env perl
use 5.012;
my @rocks = qw(aa bb cc dd ee);
print "@rocks\n";
while(my($index,$value) = each @rocks){
	say "$index:$value";
}
