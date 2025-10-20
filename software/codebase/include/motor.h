#ifndef MOTOR_H
#define MOTOR_H

#define RANGE 100
#define PWM 2
#define PIN_1 0
#define PIN_2 1
#define LARGE 10 // LARGE e a distancia de uma roda até a outra
#define MAX_V 0.47645f
#define SECOND 1000000

#ifdef __cplusplus
extern "C" { // para compatibilidade com o C++
#endif

/* Os membros left_motor e right_motor contem o numero
 * de dos pinos que ligam na ponte H onde cada indice
 * do vetor tem usa função explicada pelos macros PIN_1
 * PIN_2 e PWM
 */

struct motor {

  unsigned short int direction;
  unsigned int left_motor[3];
  unsigned int right_motor[3];
  unsigned int theta;
  unsigned int velocity;
  unsigned int second_time;
} typedef motor;

int spin(motor user_motor);

void motors_stop(motor user_motor);

int forward(motor user_motor);

#ifdef __cplusplus
}
#endif

#endif
