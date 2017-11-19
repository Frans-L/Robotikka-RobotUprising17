# Robotikka Team - Robot Uprising 17 - Hackathon 

The source code of team Robotikka's robot. The Robot Uprising is 48h hackathon, in which teams have to build and code a robot that solves a twisted race track. Team Robotikka achieved the 1st place.

## Description

The Robot Uprising 2017 was a 48h hackathon. Each team had a Lego Mindstorms NXT 2.0 kit. An idea was to build a robot that can solve various challenges. Points were given by speed, automation, result and sneakiness. In total, there were 20 teams. Our team achieved the 1st place with points 54.5p / 57p. More information about the hackathon can be found [robotuprising.fi](http://robotuprising.fi/).

## Team

* **Frans L** - coder - [Frans-L](https://github.com/Frans-L)
* **Henry P** - coder & robot builder - [Zwenkka](https://github.com/Zwenkka)
* **Pekka P** - robot designer & builder
* **Markku L** - robot designer & builder
* **Olli L** - robot designer & builder

## Code

The robot was coded with NXC.

[Bricxcc:](http://bricxcc.sourceforge.net/nbc/)
> Not eXactly C (NXC) is a high level language, similar to C, built on top of the NBC compiler.
> Next Byte Codes (NBC) is a simple language with an assembly language syntax that can be used to program LEGO's NXT programmable brick (from the new LEGO Mindstorms NXT set).


Structure:

* **Robotikka_AI.c**
    * It's the brain of the robot. It solves some challenges completely automated.
* **BluetoothController.c** 
    * It's code to remote control the robot. Robotikka_AI will stop running when BluetoothController sends orders over bluetooth.

Requirements: 

* BricxCC
* NXT Firmware 1.31 
* Rename files from *.c to *.nxc

**Note** Without the robot, the code might not be very interesting.


## License

This project is licensed under the Apache Software License 2.0.
