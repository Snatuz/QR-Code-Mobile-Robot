#ifndef MOTOR_HPP
#define MOTOR_HPP
#define SECOND 1000000


struct motor {
  
  unsigned int PWM;
  unsigned int previous_PWM = 0;
  unsigned int velocity;
  unsigned int encoder_counter = 0;
  unsigned int previous_encoder_counter = 0; 
  float error;
  float previous_error;
  float correction; 
  float derivative;
  float integral;
  
} typedef motor;


motor l_motor;
motor r_motor;
motor *left_motor = &l_motor;
motor *right_motor = &r_motor;
float KP = 0;
float KI = 0;
float KD = 0;
float setpoint = 0;


int spin();

void stop();

int forward();

#endif
