<?php

//require_once(dirname(__FILE__) ."/zookeeper-api.php");
//require_once("abc.php");

function abc_watcher($event_type, $state, $path)
{
    echo "abc_watcher called, event_type: $event_type, state: $state, path: $path\n";
}


$zk = new Zookeeper();
$zk->connect("10.108.72.190:2181", null);
$zk_state = $zk->getState();
while ($zk_state != Zookeeper::CONNECTED_STATE) {
    echo "not connected, state: $zk_state\n";
    sleep(1);
    $zk_state = $zk->getState();
}

$path = "/qlog/abc";
$state = 1048576; //Zookeeper::OK;
echo "try go get $path \n";
$info = $zk->get($path, "abc_watcher", $state); 

echo "get state: $state, result: \n";
var_dump($info);

if ($info == NULL) {
    echo "get failed, no result\n";
}

$info = json_decode($info);
echo "json decode result: \n";
var_dump($info);

if ($info == NULL) {
    echo "json decode failed, no content\n";
}

$childs = $zk->getChildren($path, "abc_watcher");
echo "get children result: \n";
var_dump($childs);

if (!is_array($childs) && count($childs) <= 0) {
    echo "no children to be geted\n";
}

?>

