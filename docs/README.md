# T300 robot 3.0 at AISVN

This is our third iteration of student created robots. Have a look:

![T300](T300-20191119.jpg)

## Subtitle

and some more

## Remote

how to control with 10 keys

- 'F' forward
- 'B' backward
- 'L' turn left
- 'R' turn right
- 'M' select (menu)
- 'S' start
- 'T' triangle
- 'C' circle
- 'X' button X
- 'Q' sQuare

## Pin assignment

| pin | general |      used for      |          note         |
|:---:|:-------:|:------------------:|:---------------------:|
| 0   |    RX   |    Bluetooth RX    |                       |
| 1   |    TX   |    Bluetooth TX    |   5V level, not 3.3!  |
| 2   |         | Ultrasonic trigger |                       |
| 3~  |         |   Ultrasonic echo  |                       |
| 4   |         |       buzzer       |   acoustic feedback   |
| 5~  |         |                    |                       |
| 6~  |         |                    |                       |
| 7   |         |                    |                       |
| 8   |         |                    |                       |
| 9~  |         |  Servo ultrasonic  |                       |
| 10~ |         |         E1         |  enable Moter 1 (PWM) |
| 11~ |         |         E2         |  enable Motor 2 (PWM) |
| 12  |         |         M1         |    forward/backward   |
| 13  |   LED   |         M2         |    forward/backward   |
| A0  |         | Servo left-right   | Robotarm 5-175        |
| A1  |         | Servo up-down      | Robotarm 45-120       |
| A2  |         | Servo forward-back | Robotarm 65-140       |
| A3  |         | Servo open-close   | Robotarm 90-125       |
| A4  |         |                    |                       |
| A5  |         |                    |                       |
| SDA | I2C     | Display 1602       | optic feedback        |
| SCL | I2C     | MPU6050            | gyroscope orientation |

## Remote control software

- iOS: BitBlue
- Android and PC: Chrome and this browser page: (https://kreier.github.io/remote) 

## Menu (select, confirmed by number of beeps from buzzer)

1. General driving
2. Ultrasonic distance with acoustic feedback
3. Autonomuous driving (start triangle, stop x)
4. Control robot arm

## History - gallery

### T500

2020-04-04

![T500](T500-20191119.jpg)

### T400

2020-02-02

![T400](T400-20191119.jpg)

### T300

2019-11-18

![T300](T300-20191119.jpg)

### asa

2019-11-04

![asa](asa-20191119.jpg)

### T200

2019-04-08

![T200](T200-20191119.jpg)

### T80

2019-03-26

![T80](T80.jpg)

### T110

2018-10-25

![T110](T110-20191119.jpg)

### T100

2018-10-09

![T100](T100-20191119.jpg)

