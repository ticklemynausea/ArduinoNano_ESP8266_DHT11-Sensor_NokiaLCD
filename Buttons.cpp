#include "Buttons.h"
#include "Routine.h"
#include "Display.h"
#include "Pushover.h"

/* button pins */
uint8_t Buttons::pinout[NUM_BUTTONS] = {GPIO_BUTTON_A, GPIO_BUTTON_B};

/* button state */
uint8_t Buttons::state[NUM_BUTTONS];

void (*Buttons::callbacks[NUM_BUTTONS])() = {
  &Display::StatusScreen,
  &Pushover::Test,
};


/* Buttons */
void Buttons::Initialize() {

  FOR_b {
    pinMode(Buttons::pinout[b], INPUT_PULLUP);
    Buttons::state[b] = HIGH;
  }

}

void Buttons::Read() {

  FOR_b {
    uint8_t new_state = digitalRead(Buttons::pinout[b]);
    uint8_t previous_state = Buttons::state[b];

    // check if the pushbutton is pressed.
    // if it is, the state is HIGH:
    if (new_state == LOW && previous_state == HIGH) {
      Buttons::callbacks[b]();
      Buttons::state[b] = new_state;
    }
    
    if (previous_state == LOW && new_state == HIGH) {
      Buttons::state[b] = new_state;      
    }
  }

}

bool Buttons::IsPressed(uint8_t gpio) {
  return (digitalRead(gpio) == LOW);
}
