#!/usr/bin/env perl

$fred[0] = 100;
$fred[1] = 40;
$fred[2] = 30;
$fred[3] = 12;

print $fred='aaa';
print $fred[0] .".";
print $fred[1] .".";
print $fred[2] .".";
print $fred[3] ."\n";
print "{$fred}[3]\n";#print "$fred.[3] or print "$fred\[3]
print $fred[2.8-1] ."\n";
print "$#fred\n"; # list end index 
print "$fred[$#fred]\n"; # the last value
print "$fred[-1]\n"; # the last value

@list1=(1,2,3,4,5);
print "@list1\n";

#@list1=(1..100);
#print "@list1\n";

@list1=($fred[1],1..5);
print "@list1\n";

@list1=(0..$#fred);
print "@list1\n";
@list2= reverse @list1;
print "@list2\n";
@list=("aa","bb","cc","dd","ee");
print "@list\n";

@list=qw(aa bb cc dd ee);
print "@list\n";

@list=qw/aa bb cc dd ee/;
print "@list\n";

($a,$b,$c)=(1,2,3);
print "$a,$b,$c\n";
($a,$b,$c)=($c,$a,$b);
print "$a,$b,$c\n";
($a,$b,$c)=qw(This is bug);
print "$a $b $c\n";

for $rock (qw/a b c d e/){
	print "$rock ";
}
print "\n";

foreach $rock (qw/a b c d e/){
	print "$rock ";
}
print "\n";

foreach (1..10){
	print "The value is $_\n";
}
