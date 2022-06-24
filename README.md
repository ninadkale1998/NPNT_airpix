This code connects to the server on which user will verify and will be given permission, if verfied, to fly. Till permission is not received, Drone will not be armed i.e. all PPM singals are blocked by Arduino. Once permission is granted, all 8 channel PPM singal will be read through Arduino and written on Pixhawk module.
There is another mode call Return to launch, where arduino write 1700 PPM on last channel to trigger that mode.

Platform -> Arduino Uno with SIM900a

Communication method - AT commands
