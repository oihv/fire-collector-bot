# Autobot

An auto "Ore" collector bot for a university-level competition made with custom STMF103C6T6 board.

To do list:

- [ ] Implement Infrared (IR) sensor
- [x] Implement photoelectric sensor
- [ ] Make the following module for the motor movement:
  - [ ] Move forward
  - [ ] Turn left/right
- [x] Implement servo for claw
- [x] Implement another pin for second servo
- [ ] Learn PID and how to apply it to the robot
- [ ] Connect gray scale sensor
- [ ] Line following robot

**For each of these features, we need to figure out how to connect the component to the board, through what pin, how to receive and process the input, and so on.**

## Controlling servo

Connect the servo to PWM2 pin and/or PWM1 pin (PA1 and PA0), and then use
`TIM_SetCompare2(TIM2, value) function,`
since the servo is a continous rotation servo, it runs indefinitely without a specific angle. Here's the parameter

- 175 = max speed counter clockwise, 184 = min counter clockwise
- 185 = stop
- 195 = max speed clockwise, 186 = min clockwise

## Photo electric sensor switch

Here is the map for the cable:

- blue: negative polarity (ground/GND)
- brown: positive polarity (5V)
- black: data (GPIO pin)

## Infrared Sensor
