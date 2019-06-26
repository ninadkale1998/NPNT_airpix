Platform - Arduino Uno with SIM900a for gprs connection
Communication method - AT commands
what does this code do: It connect to the server on which user will verify and after rules check, permission is given. Till permission is recived, Drone is not armed i.e. all PPM singals are blocked by arduino
Once permission is granted, all 8 channel PPM singal will be read through arduino and write on Pixhawk module.
There is another mode call Return to launch. Where arduino write 1700 PPM on last channel to trigger that mode.
