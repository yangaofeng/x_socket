<?php

$a = "hello";

function my_echo ()
{
    $a = "world";
    echo $a;
    var_dump($a);
}

my_echo();


$arr = array('a'=>1, 'b'=>2, 'c'=>3);
reset($arr);
while (list($key, $val) = each($arr)) {
    /* Do something with $key and $val */
    echo $key, "=>", $val, "\n";
}
reset($arr);
$firstkey = key($arr);
$firstval = current($arr);
$bval = next($arr);
$cval = next($arr);

?>
