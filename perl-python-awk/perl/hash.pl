#!/usr/bin/env perl

%some_hash = ('foo',35,'bar',12.4,2.5,'hello','wilma',1.72e30,'betty',"bype");
@any_array = %some_hash;
print "@any_array\n";
while(($a,$b)=each %some_hash){
	print "$a\t ==> $b\n";
}
print "$ENV{PATH}\n";
