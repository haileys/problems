#!/usr/bin/env perl

$r = shift;
$c = $r;

print "$r $c\n";
for($y = 0; $y < $r; $y++)
{
	for($x = 0; $x < $c; $x++)
	{
		print ($x + $y);
		print " ";
	}
	print "\n"
}
