# Fire bot

A "fire" collector robot for an undergraduate competitition made with ??? board.

## To do list:
- [x] Moves 12v motor x 4
- [ ] 5v motor x2 (both uses pwm/TIM)
- [x] Moves servo
- [ ] PID (proportional–integral–derivative controller) mechanism
- [ ] Receive input from 7 pin grayscale sensor
- [ ] built in mpu6070 (accelorometernya, perlu banget nanti)
- [ ] how to convert accelerometer output to position
- [ ] low pass filter
- [ ] receive flame location from CH4502
    - [ ] Simple row by row input (with backspace and enter)
    - [ ] Map each button to the cell in the matrix, hit the button to increment

## Prerequisite Knowledge
GPIO (General Purpose Input Output) - [for setting pin high or low]

TIM (Timer) - [for controlling motor, servo]

ADC (Analog Digital Converter) - [for receiving sensor]

USART (Universal Synchronous Asynchronous Receiver Transmitter) - [for communicating with other device that uses USART bus]

CAN (Controller Area Network) - [for communicating with other device that uses CAN bus]

IT (Interrupt) - [for checking input all types of peripheral]

DMA (DIrect Memory Access) - [for optimizing data transfer all types of peripheral]
