#!/usr/bin/env perl

#open MYFILE,'>a.log';
#print MYFILE "Hello,world";
#close MYFILE;
#use autodie;
#open(MYFILE,'a.log') or die "$!";

#if(!open(MYFILE,'a.log')){
#	die "Error:$!";
#}
#while (<MYFILE>){
#	print $_;
#}
#close MYFILE;
while (($a,$b) = each %ENV){
	print "$a=$b\n";
}
