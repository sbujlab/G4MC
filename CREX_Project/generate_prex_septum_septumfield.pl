#!/usr/bin/perl
# Program: generate_prex_septumfield.pl
# Date   : 30 Sep., 2014
# Author : N. A. N. Hirlinger Saylor
# Purpose: Generate septum field map for PREX using rtsep102008.map from SNAKE (Guido)
# Usage  : ./generate_prex_septumfield.pl
# Input  : rtsep102008.map from the same directory
# Output : prex_septumfield.dat to the same directory
################################################################

use warnings;
use diagnostics;
use strict;

open INFILE, "<rtsep102008.map";
my $a_code_for_snake = <INFILE>; chomp $a_code_for_snake; #ignored in this code
my $symmetry         = <INFILE>; chomp $symmetry;         #ignored in this code
my $x_input          = <INFILE>; chomp $x_input;          #will contain number of x points, x min and x max
my $y_input          = <INFILE>; chomp $y_input;          #will contain number of y points, y min and y max
my $z_input          = <INFILE>; chomp $z_input;          #will contain number of z points, z min and z max
my $format           = <INFILE>; chomp $format;           #ignored in this code
my @input            = ($x_input, $y_input, $z_input);    #make loop easy with arrays
my @n;
my @min;
my @max;
my @step;
#We are reading the limits in x, y and z, as well as the number of points.

for ( my $i = 0; $i < 3; $i++ ) {
    if( $input[$i] =~ /(\d+) (\-?\d+\.\d) (\-?\d+\.\d)/ ){
	$n[$i]    = $1; $min[$i] = $2; $max[$i] = $3;
	$step[$i] = ( $max[$i] - $min[$i] ) / ( $n[$i] - 1 );
	#print "number of points: $n[$i]\nmin: $min[$i]\nmax: $max[$i]\n";
    }
}

#Slurp the rest

my @lines = <INFILE>;
close INFILE;

#reading in the data from the weird format:
# x y z x y
# z x y z x 
# y z x y z
# x y ETC.......

my @x; my @y; my @z;
my @mat = ( \@x, \@y, \@z );
my $index = 0;
for( @lines ) {
    my @numbers = ( $_ =~ /(\-?\d\.\d+(?:E(?:\+|\-|\W)?\d+)?)/g ); # Format: -0.26962998E-05
    #print "@numbers\n";
    my $len = @numbers;
    if( $len != 5 ) {
	#print $_;
	die "error $len\n";
    }
    for ( @numbers ) {
	push( @{$mat[ $index % 3 ]}, $_ );
	$index++;
	#print "$_ ";
    }
    #print "\n";
}

#sanity check:

#for( my $i = 0; $i < 3; $i++ ) {
    #my $len = @{$mat[$i]};
    #print "$len\n";
#}

open OUTFILE, ">prex_septumfield.dat";

print OUTFILE "           169          39         101           1\n" ;
print OUTFILE " 1 x [LENGU]\n" ;
print OUTFILE " 2 y [LENGU]\n" ; 
print OUTFILE " 3 z [LENGU]\n" ;
print OUTFILE " 4 bx [FLUXU]\n" ;
print OUTFILE " 5 by [FLUXU]\n" ;
print OUTFILE " 6 bz [FLUXU]\n" ;
print OUTFILE " 0     x        y        z        Bx        By        Bz\n" ;

my $index2 = 0;

for( my $k = 0; $k < $n[2]; $k++ ) {
    for( my $j = 0; $j < $n[1]; $j++ ) {#switch indices
	for( my $i = 0; $i < $n[0]; $i++ ) {#switch indices
	    my $my_x = $min[0] + $i * $step[0];
	    my $my_y = $min[1] + $j * $step[1];
	    my $my_z = $min[2] + $k * $step[2];
	    $my_x /= 10;
	    $my_y /= 10;
	    $my_z /= 10;
	    $x[$index2] *= 4.7760707;
	    $y[$index2] *= 4.7760707;
	    $z[$index2] *= - 4.7760707;
	    #if ( $my_y >= 0 ) {
	    #print OUTFILE "$my_x $my_z $my_y $x[$index2] $z[$index2] $y[$index2]\n";
	    print OUTFILE "$my_x $my_y $my_z $x[$index2] $y[$index2] $z[$index2]\n";
	    #}
	    $index2++;
	}
    }
}

close OUTFILE;
