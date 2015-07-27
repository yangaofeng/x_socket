<?php

//演示直接创建变量，在active_symbol_table中，变量在外部可直接使用
create_foo();
echo $foo, "\n";

//创建并返回一个变量,符号表由php来管理
$str = return_string();
echo $str, "\n";

//创建一个数组并返回
var_dump(return_array());

//测试引用调用
$a = "hello";

ref_call($a);
echo "非引用调用，a=", $a, "\n";

ref_call(&$a);
echo "引用调用，a=", $a, "\n";

?>

