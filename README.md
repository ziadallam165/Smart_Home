# Smart_Home
A smart home with 5 main features.
1- Control light by opening it for a certain amount of time
2- Control the temperature
3- Open/Close door
4- Emergency Button
5- Password protected

The drivers used:

For MCAL:
1- DIO
2- UART
3- Timer
4- ADC
5- GIE

For HAL:
1- LCD
2- DC-motor
3- Stepper Motor
4- Temperature sensor

-We used the timer peripheral to control for how long will the led be turned on
-We used the interrput peripheral to implment the emergency Button
-We used the ADC Peripheral for the temprature sensor
-We used USART communication protocol to get input from the User

The User would interact with the User terminal and enter the Password if he/she enters the wrong Password 3 times the buzzer will be turned on and all the features of the smart home will be shut off, if the right Password was given it will then display the features on the LCD.
