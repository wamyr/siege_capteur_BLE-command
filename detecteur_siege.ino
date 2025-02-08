
#include <BleGamepad.h>  // Inclure la bibliothèque du gamepad BLE
//#include <BleKeyboard.h>  // Inclure la bibliothèque BLE Keyboard

const int pinA0 = 0;  // GPIO A0 (vérifie bien que c'est le bon GPIO)
int There_is_someone = -1;
unsigned long start_timer;

BleGamepad bleGamepad;   // Crée un objet gamepad BLE
//BleKeyboard bleKeyboard("ESP32 Keyboard", "Espressif", 100);  // Nom de l'appareil Bluetooth

#define True 1
#define False 0
#define Waiting -1

// Déclarations des fonctions
void Someone_just_sit();
void Someone_just_left();
void start_game();
void reset_game();

void setup() {
  Serial.begin(115200);  // Initialisation de la communication série
  bleGamepad.begin();               // Initialise le Gamepad BLE
  //bleKeyboard.begin();    // Initialisation du clavier BLE
  pinMode(pinA0, INPUT);  // Configuration du pin en entrée

  // Attacher les interruptions
  attachInterrupt(digitalPinToInterrupt(pinA0), detectFalling, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinA0), detectRising, RISING);
}

void loop() {
  if (There_is_someone == True) {
    Someone_just_sit();
    There_is_someone = Waiting;
  }
  if (There_is_someone == False) {
    Someone_just_left();
    There_is_someone = Waiting;
  }
  Serial.println("hello");
}

//
void detectFalling() {
  There_is_someone = True;
}

//
void detectRising() {
  There_is_someone = False;
}

void start_game() {
  bleGamepad.press(BUTTON_1);
  /*bleKeyboard.press(KEY_LEFT_CTRL);  // Appuie sur la touche Ctrl
  bleKeyboard.press('.');            // Appuie sur la touche 'C'
  delay(100);                        // Maintient les touches enfoncées pendant 100 ms
  bleKeyboard.releaseAll();          // Relâche toutes les touches
  delay(400);*/
}

void reset_game() {
  bleGamepad.press(BUTTON_2);
  /*bleKeyboard.press(KEY_LEFT_CTRL);  // Appuie sur la touche Ctrl
  bleKeyboard.press(',');            // Appuie sur la touche 'C'
  delay(100);                        // Maintient les touches enfoncées pendant 100 ms
  bleKeyboard.releaseAll();          // Relâche toutes les touches
  delay(400);*/
}

void Someone_just_sit() {
  start_timer = millis();
  while (millis() - start_timer < 400) {
    if (There_is_someone != True) {
      There_is_someone = Waiting;
      return;
    }
  }
  start_game();
}

void Someone_just_left() {
  start_timer = millis();
  while (millis() - start_timer < 1500) {
    if (There_is_someone != False) {
      There_is_someone = Waiting;
      return;
    }
  }
  reset_game();
}
