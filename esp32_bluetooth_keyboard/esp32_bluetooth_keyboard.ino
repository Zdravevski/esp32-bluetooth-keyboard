// The script is written by Slavko Zdravevski
// If you want to support my work, you can subscribe to my youtube channel: https://bit.ly/3FG9hpK
// You can check this video: https://youtu.be/Y4vDdVLjCtg, I explained the code and the circuit as well
// I do a lot of interesting things in my free time, so you might find something of your interest or we can exchange ideas and knowledge

#define USE_NIMBLE
#include <BleKeyboard.h> //https://github.com/T-vK/ESP32-BLE-Keyboard

BleKeyboard bleKeyboard("Retro Keyboard", "Zdravevski", 100);

#define KEY_NUMBER 18
// LEFT PART OF THE KEYBOARD
#define W_KEY 15
#define A_KEY 0
#define S_KEY 4
#define D_KEY 16
#define E_KEY 17
#define R_KEY 5
#define T_KEY 18
#define Y_KEY 19

// RIGHT PART OF THE KEYBOARD
#define UP_KEY 13
#define LEFT_KEY 12
#define DOWN_KEY 14
#define RIGHT_KEY 27
#define Z_KEY 26
#define X_KEY 25
#define C_KEY 33
#define V_KEY 32

// EXTRA KEYS
#define TAB_KEY 23
#define ENTER_KEY 22

bool keyStates[KEY_NUMBER] = {false, false, false, false, false, false, false, false,
                      false, false, false, false, false, false, false, false, false, false};
                      
int keyPins[KEY_NUMBER] = {W_KEY, A_KEY, S_KEY, D_KEY, E_KEY, R_KEY, T_KEY, Y_KEY, UP_KEY, 
                  LEFT_KEY, DOWN_KEY, RIGHT_KEY, Z_KEY, X_KEY, C_KEY, V_KEY, TAB_KEY, ENTER_KEY};
                  
uint8_t keyCodes[KEY_NUMBER] = {'w', 'a', 's', 'd', 'e', 'r', 't', 'y', KEY_UP_ARROW, KEY_LEFT_ARROW,
                       KEY_DOWN_ARROW, KEY_RIGHT_ARROW, 'z', 'x', 'c', 'v', KEY_TAB, KEY_RETURN};


void setup() {
  Serial.begin(115200);

  pinMode(W_KEY, INPUT_PULLUP);
  pinMode(A_KEY, INPUT_PULLUP);
  pinMode(S_KEY, INPUT_PULLUP);
  pinMode(D_KEY, INPUT_PULLUP);
  pinMode(E_KEY, INPUT_PULLUP);
  pinMode(R_KEY, INPUT_PULLUP);
  pinMode(T_KEY, INPUT_PULLUP);
  pinMode(Y_KEY, INPUT_PULLUP);

  pinMode(UP_KEY, INPUT_PULLUP);
  pinMode(LEFT_KEY, INPUT_PULLUP);
  pinMode(DOWN_KEY, INPUT_PULLUP);
  pinMode(RIGHT_KEY, INPUT_PULLUP);
  pinMode(Z_KEY, INPUT_PULLUP);
  pinMode(X_KEY, INPUT_PULLUP);
  pinMode(C_KEY, INPUT_PULLUP);
  pinMode(V_KEY, INPUT_PULLUP);

  pinMode(TAB_KEY, INPUT_PULLUP);
  pinMode(ENTER_KEY, INPUT_PULLUP);
  
  bleKeyboard.begin();
}

bool connectNotificationSent = false;

void loop() {
  int counter;
  if(bleKeyboard.isConnected()) {
    if (!connectNotificationSent) {
      Serial.println("Code connected...");
      connectNotificationSent = true;
    }
    for(counter = 0; counter < KEY_NUMBER; counter ++){
      handleButton(counter);
    }
  }
}

void handleButton(int keyIndex){
  if (!digitalRead(keyPins[keyIndex])){
    if (!keyStates[keyIndex]){
      keyStates[keyIndex] = true;
      bleKeyboard.press(keyCodes[keyIndex]);
    }
  }
  else {
    if (keyStates[keyIndex]){
      keyStates[keyIndex] = false;
      bleKeyboard.release(keyCodes[keyIndex]);
    }
  }
}
