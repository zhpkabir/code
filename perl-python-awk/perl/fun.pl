#!/usr/bin/env perl
use strict;
#use 5.012;
sub sum {
	my $sum;
	foreach (1..100){
		 $sum+=$_;
	}
	$sum;
}

my $value = &sum;
print "value=$value\n";

sub max {
	if( $_[0]<$_[1]){
		$_[1];
	}
	else {
		$_[0];
	}
}

$value = &max(4);
print "value=$value\n";

$value=max2(1,2);
print "value=$value\n";

sub max2{
	my $tmp = shift @_;
	foreach (@_) {
		if($_ > $tmp){
			$tmp = $_;
		}
	}
	$tmp
}

$value=max2 1,2,3;
print "value=$value\n";

$value=&max2(1,2,3,4,5);
print "value=$value\n";

$value=&max2(5);
print "value=$value\n";


sub chomp(){
	print "Hello,chomp\n"
}

&chomp;


