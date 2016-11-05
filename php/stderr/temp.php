<?php
$descriptorspec = array(
    0 => array("pipe", "r"),  // stdin
    1 => array("pipe", "w"),  // stdout
    2 => array("pipe", "w"),  // stderr
);

$process = proc_open('./test.sh', $descriptorspec, $pipes, dirname(__FILE__), null);

$stdout = stream_get_contents($pipes[1]);
fclose($pipes[1]);

$stderr = stream_get_contents($pipes[2]);
fclose($pipes[2]);

echo "stdout : \n";
var_dump($stdout);

echo "stderr :\n";
var_dump($stderr);

?>
