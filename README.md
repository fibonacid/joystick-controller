# Joystick Controller
for audio spatialization and more.

This project involves an Arduino board, a black plastic box and Joystick controller.
The goal is to create a physical interface that enables the user to manipulate multi-dimensional data spaces in the most simple and cost effective way.

I decided to give it a shot with a joystick controller: 
an input device consisting in a stick that pivots on a base and reports its angle or direction to the device it is controlling [wiki](https://en.wikipedia.org/wiki/Joystick)

From this kind of sensor you can extrapolate many values and gestures such as the XY position of the “cursor” or  its distance from the center of the plane or from all its 4 corners.
Discrete gestures are also possible: most joysticks can be clicked and with software one could decode arrow like commands such as UP, RIGHT, DOWN & LEFT and its doubled counterparts.
Another important feature of this particular input device is that it’s cheap to produce and that has been out there since forever, wether it was attached to a gaming console, an arcade or a jet anyone born in the last century could say to have an idea of what it is and how it should be used.

To actually create the device I used an Arduino Uno board connected to a [joystick module](https://tkkrlab.nl/wiki/Arduino_KY-023_XY-axis_joystick_module) from a manufacturer named Keyes. In addition to this I added a LED indicator to
provide some feedback to the user. The whole system is enclosed in a black plastic case i recycled from home.

The joystick module has the following pins.

...

The ground and 5V will be connected to the respective ports on the Arduino while the `VR_X` and `VR_Y` pins to the analog peripherals `A0` and `A1`, lastly the switch pin which will be connected to the digital pin `D2`.

The LED indicator will be connected to the digital pin `D3`, a special pin that can perform Pulse Width Modulation (PWM) which can be use ti alter the perceived brightness of the component. 
For more detailed information about the hardware plan click this [link](https://github.com/lorenzorivosecchi/joystick-controls-stuff/blob/master/Arduino/schematics.png) and to know more about the software that runs on the Arduino visit this [link](https://github.com/lorenzorivosecchi/joystick-controls-stuff/blob/master/Arduino/joystick/joystick.ino).

For demonstration purposes i decided to apply this technology to task of sound spatialization. This application came to my mind because in gaming the joystick is used almost all the time used to control the position of the played character and its view point.

The algorithm i used is very very simple and can be summarized in pseudo-code like this:
- Read serial port (in this case _usbodem14201_).
- Parse data to obtain a value for X and Y.
- Use X and Y to make a point inside a coordinate system.
- Calculate 4 weights based on the distance from the point to each corner of the plane.
- Normalize the weights.
- Use each weight to scale the level of a quadriphonic stream of audio.
- Use each weight to delay the audio stream by a maximum of 50 ms.

The complete Max MSP patches can be found at this [link](https://github.com/lorenzorivosecchi/joystick-controls-stuff/tree/master/Max).

# Conclusions
I am satisfied about the simplicity of the device, however i think that there is room for improvement. I think that the experience would be better if the joystick was taller, allowing a more fine tuned control of the angle. Also i feel that it would be good to have the possibility to lock the controller at a certain angle.
These features are probably already available using one of those controllers for flight simulations,
so it would be worth while checking online for hackable models.
