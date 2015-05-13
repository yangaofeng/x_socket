#!/usr/bin/env php
<?php 
$in=fopen("php://stdin","r");
$out_array=array();
while ($line=fgets($in)){
    $wordlist=str_word_count($line,1);
    foreach($wordlist as $word){ 
        print "$word\t1\n";
    } 
}
fclose($in);
?>
