#!/usr/bin/env perl

$primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271];

$nsymbols = 0;
$nloops = 0;
for(@$primes) {
	last if $nsymbols + $_ > 200;
	$nsymbols += $_;
	$nloops++;
}

print "$nsymbols 200\n";

$j = 1;
$sum = 0;
for($i = 0; $i < $nloops; $i++) {
	$origj = $j++;
	$sum += $primes->[$i];
	for(; $j <= $sum; $j++) {
		print "$j ";
	}
	print "$origj ";
}
print "\n";

for($i = 1; $i <= 200; $i++) {
	print "$i ";
}