<?php

//对象由haha模块生成
//class baby {
//    public function __construct() {
//        echo "a new baby!\n";
//    }
//
//    public function hello() {
//        echo "hello world!\n";
//    }
//}


//调用haha模块里边的test_call函数，
//生成baby类，并调用构造和hello方法，最后析构销毁对象
test_call();

//调用haha模块的test_return，返回一个对象，
//并且在返回对象前，在test_return函数内部调用构造函数
$obj = test_return();
$obj->hello();

//在php代码里用new创建对象，baby类由haha模块导出
$obj = new baby();
$obj->hello();

?>

