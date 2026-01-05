#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <pico/time.h>
#include <stdint.h>

#include "./utils.h"

#define LED_PIN 25
#define BLINK_INTERVAL_US 500000

uint8_t led_state = 0;

void toggle_led(absolute_time_t *t) {
  int64_t delta_us = absolute_time_diff_us(*t, get_absolute_time());
  if (delta_us > BLINK_INTERVAL_US) {
    *t = get_absolute_time();

    // Pico
    gpio_xor_mask(1u << LED_PIN);

    // Pico W
    led_state ^= 1;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state);
  }
}

int main() {
  char last_chars[SERIAL_BUFFSIZE];
  absolute_time_t led_time_ref = get_absolute_time();

  stdio_init_all();
  sleep_ms(1000);
  stdio_set_chars_available_callback(input_callback, &last_chars);

  // Pico
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  // Pico W
  cyw43_arch_init();

  while (true) {
    sleep_ms(5);
    toggle_led(&led_time_ref);
  }
}
