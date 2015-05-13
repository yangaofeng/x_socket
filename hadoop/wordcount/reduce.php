#!/usr/bin/env php
<?php 
$in = fopen("php://stdin", "r");

$res_array = array();

while ($line = fgets($in)) {

    list($word, $count) = split("\t", $line);
    $word = trim($word);
    $count = trim($count);

    if ($word != "") {
        $key = $word;
        if (isset($res_array[$key])) {
            $res_array[$key] += $count;   # 对相同的key值进行累加
        } else {
            $res_array[$key] = $count;   # 对相同的key值进行累加
        }
    }
}

fclose($in);

foreach ($res_array as $key => $value)
{
    print "$key\t$value\n";          # 以\t分隔key和value
}
?>
