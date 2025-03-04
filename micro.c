#include <reg51.h>

// Define pins for IR sensors
sbit IR_Left = P1^0;   // Left IR sensor
sbit IR_Front = P1^1;  // Front IR sensor
sbit IR_Right = P1^2;  // Right IR sensor

// Define pins for motor control
sbit Motor_Left_Forward = P2^0;
sbit Motor_Left_Backward = P2^1;
sbit Motor_Right_Forward = P2^2;
sbit Motor_Right_Backward = P2^3;

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1275; j++);
}

void stop() {
    Motor_Left_Forward = 0;
    Motor_Left_Backward = 0;
    Motor_Right_Forward = 0;
    Motor_Right_Backward = 0;
}

void move_forward() {
    Motor_Left_Forward = 1;
    Motor_Left_Backward = 0;
    Motor_Right_Forward = 1;
    Motor_Right_Backward = 0;
}

void move_backward() {
    Motor_Left_Forward = 0;
    Motor_Left_Backward = 1;
    Motor_Right_Forward = 0;
    Motor_Right_Backward = 1;
}

void turn_left() {
    Motor_Left_Forward = 0;
    Motor_Left_Backward = 0;
    Motor_Right_Forward = 1;
    Motor_Right_Backward = 0;
}

void turn_right() {
    Motor_Left_Forward = 1;
    Motor_Left_Backward = 0;
    Motor_Right_Forward = 0;
    Motor_Right_Backward = 0;
}

void main() {
    while (1) {
        if (IR_Front == 1) {  // Obstacle in front
            stop();
            delay(100);
            if (IR_Left == 0) {
                turn_left();
                delay(200);
            } else if (IR_Right == 0) {
                turn_right();
                delay(200);
            } else {
                move_backward();
                delay(200);
            }
        } else if (IR_Left == 1) {  // Obstacle on the left
            turn_right();
            delay(200);
        } else if (IR_Right == 1) {  // Obstacle on the right
            turn_left();
            delay(200);
        } else {
            move_forward();  // No obstacles
        }
        delay(100);
    }
}
