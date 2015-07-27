<?php

//create a 5 gear car
$car = new Car(5);
echo "car current speed: ", $car->getCurrentSpeed(), "\n";  // prints '0'

$car->accelerate();
echo "car current speed: ", $car->getCurrentSpeed(), "\n"; // prints '5'

$bike = new Bike(2);
echo "bike current speed: ", $bike->getCurrentSpeed(), "\n";  // prints '0'

$bike->accelerate();
echo "bike current speed: ", $bike->getCurrentSpeed(), "\n"; // prints '5'

?>
