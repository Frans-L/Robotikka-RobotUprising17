# Robotikka Team - Robot Uprising 17 - Hackathon 

The source code of the winning robot in Robot Uprising 17. Robot Uprising is Finland's largest robot hackathon, in which teams have to build and code a robot that solves a twisted race track. 

## Description

The Robot Uprising 2017 is a 48h hackathon. Each team had a Lego Mindstorms NXT 2.0 kit. An idea was to build a robot that can solve various challenges. Points were given by speed, automation, result, and sneakiness. In total, there were 20 teams. Our team achieved the 1st place with points 54.5p / 57p. More information about the hackathon can be found [robotuprising.fi](http://robotuprising.fi/).

## Structure

* **Robotikka_AI.c**
    * It's the brain of the robot. It solves some challenges automatically by using its sensors.
* **BluetoothController.c** 
    * Remote controller of the robot. Robotikka_AI will stop running when BluetoothController sends orders over Bluetooth.

## Requirements:

* BricxCC
* NXT Firmware 1.31 
* Rename files from *.c to *.nxc

**Note** Without the robot, the code might not be very interesting.

---

## Team

* **Frans L** - programmer - [Frans-L](https://github.com/Frans-L)
* **Henry P** - programmer & robot builder - [Zwenkka](https://github.com/Zwenkka)
* **Pekka P** - robot designer & builder
* **Markku L** - robot designer & builder
* **Olli L** - robot designer & builder

## License

This project is licensed under the Apache Software License 2.0.
