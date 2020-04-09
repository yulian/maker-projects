/* Key mapping for Player1 and Player2
 *  
 *  UP        - 1P:Up arrow key,    2P:'R'
 *  DOWN      - 1P:Down arrow key,  2P:'F'
 *  LEFT      - 1P:Left arrow key,  2P:'D'
 *  RIGHT     - 1P:Right arrow key, 2P:'G'
 *  ButtonA   - 1P:'B',             2P:'A'
 *  ButtonB   - 1P:'N',             2P:'S'
 *  ButtonC   - 1P:'H',             2P:'Q'
 *  ButtonD   - 1P:'J',             2P:'W'
 *  
 *  March 10th in 2020 Made by Maker Mentor
 *  
 */

// P1 for Player1, P2 for Player2
#define P1

#include <Keyboard.h>

void setup() {
  pinMode(4, INPUT_PULLUP);   // START(I | 2)
  pinMode(5, INPUT_PULLUP);   // SELECT(O | 6)
  pinMode(6, INPUT_PULLUP);   // B | A
  pinMode(7, INPUT_PULLUP);   // N | S
  pinMode(8, INPUT_PULLUP);   // H | Q
  pinMode(9, INPUT_PULLUP);   // J | W
}

void loop() {

  // Pin number of Joystick
  int currentX = analogRead(A0);
  int currentY = analogRead(A1);

  // Moving LEFT
  if(currentX == 1023) {
    #ifdef  P1
      Keyboard.press(KEY_LEFT_ARROW);
    #else
      Keyboard.press('D');
    #endif
  } else {
    #ifdef  P1
      Keyboard.release(KEY_LEFT_ARROW);
    #else
      Keyboard.release('D');
    #endif
  }

  // Moving RIGHT
  if(currentX == 0) {
    #ifdef  P1
      Keyboard.press(KEY_RIGHT_ARROW);
    #else
      Keyboard.press('G');
    #endif
  } else {
    #ifdef  P1
      Keyboard.release(KEY_RIGHT_ARROW);
    #else
      Keyboard.release('G');
    #endif
  }

  // Moving UP
  if(currentY == 1023) {
    #ifdef  P1
      Keyboard.press(KEY_UP_ARROW);
    #else
      Keyboard.press('R');
    #endif
  } else {
    #ifdef  P1
      Keyboard.release(KEY_UP_ARROW);
    #else
      Keyboard.release('R');
    #endif
  }

  // Moving DOWN
  if(currentY == 0) {
    #ifdef  P1
      Keyboard.press(KEY_DOWN_ARROW);
    #else
      Keyboard.press('F');
    #endif
  }
  else {
    #ifdef  P1
      Keyboard.release(KEY_DOWN_ARROW);
    #else
      Keyboard.release('F');
    #endif
  }

  // Pin number of Keyboard
  int bStart = digitalRead(4);
  int bSelect = digitalRead(5);
  int bControlA = digitalRead(6);
  int bControlB = digitalRead(7);
  int bControlC = digitalRead(8);
  int bControlD = digitalRead(9);

  // 'START' button
  if(bStart == LOW) {
    #ifdef  P1
      Keyboard.press('I');
    #else
      Keyboard.press('2');
    #endif
  }
  else {
    #ifdef  P1
      Keyboard.release('I');
    #else
      Keyboard.release('2');
    #endif
  }

  // 'SELECT' button
  if(bSelect == LOW) {
    #ifdef  P1
      Keyboard.press('O');
    #else
      Keyboard.press('6');
    #endif
  }
  else {
    #ifdef  P1
      Keyboard.release('O');
    #else
      Keyboard.release('6');
    #endif
  }

  // 'A' button
  if(bControlA == LOW) {
    #ifdef  P1
      Keyboard.press('B');
    #else
      Keyboard.press('A');
    #endif
  }
  else {
    #ifdef  P1
      Keyboard.release('B');
    #else
      Keyboard.release('A');
    #endif
  }

  // 'B' button
  if(bControlB == LOW) {
    #ifdef  P1
      Keyboard.press('N');
    #else
      Keyboard.press('S');
    #endif
  }
  else {
    #ifdef  P1
      Keyboard.release('N');
    #else
      Keyboard.release('S');
    #endif
  }

  // 'C' button
  if(bControlC == LOW) {
    #ifdef  P1
      Keyboard.press('H');
    #else
      Keyboard.press('Q');
    #endif
  }
  else {
    #ifdef  P1
      Keyboard.release('H');
    #else
      Keyboard.release('Q');
    #endif
  }

  // 'D' button
  if(bControlD == LOW) {
    #ifdef  P1
      Keyboard.press('J');
    #else
      Keyboard.press('W');
    #endif
  }
  else {
    #ifdef  P1
      Keyboard.release('J');
    #else
      Keyboard.release('W');
    #endif
  }

  delay(10);
}
