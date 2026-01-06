
#ifndef MYPWM_H
#define MYPWM_H

#include "hardware/pwm.h"
#include <hardware/gpio.h>
#include <pico/time.h>

#define SERVO_PIN 16
// Slow down Pico clock, 125MHz / 125 = 1 MHz
#define PICO_CLK_DEFAULT 125000000
#define CLK_DIVISOR 125.0
// Duty cycle is 1,000,000 * 0.02 seconds (50Hz)
#define PWM_STEPS PICO_CLK_DEFAULT / CLK_DIVISOR * 0.02

extern uint slice_num;
extern uint channel;
extern float min_ms;
extern float max_ms;

void pwm_set_ms(float ms);
void pwm_set_degrees(float degrees);

#ifdef MYPWM_IMPLEMENTATION

uint slice_num;
uint channel;
float min_ms;
float max_ms;

void pwm_set_ms(float ms) {
  uint single_ms_distance = PWM_STEPS / 20;
  pwm_set_chan_level(slice_num, channel, ms * single_ms_distance);
}

void pwm_set_degrees(float degrees) {
  float ms = min_ms + (degrees / 180.0) * (max_ms - min_ms);
  pwm_set_ms(ms);
}

void pwm_init_example(uint servo_pin, float _min_ms, float _max_ms) {
  // 0.5ms → 2.5ms (eg. EMAX 17g servo)
  min_ms = _min_ms;
  max_ms = _max_ms;

  gpio_set_function(servo_pin, GPIO_FUNC_PWM);

  slice_num = pwm_gpio_to_slice_num(servo_pin);
  channel = pwm_gpio_to_channel(servo_pin);

  pwm_set_clkdiv(slice_num, CLK_DIVISOR);
  pwm_set_wrap(slice_num, PWM_STEPS);
  pwm_set_enabled(slice_num, true);
}

#endif // MYPWM_IMPLEMENTATION
#endif // MYPWM_H
