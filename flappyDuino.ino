#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#include "Sprite.h"
#include "Chym.h"
#include "Bar.h"

Chym player;
Bar bar; Bar bar2;
int gameScore = 0;

int KNOCK_PIN = 2;
int LED_PIN = 8;

boolean clicked = false;

void loop(){}

void resetGame() {
  player.respawn();
  bar.setPos(0, 20);
  bar2.setPos(50, 30);
  gameScore = 0;
}

void setup() {
  Serial.begin(9600);

  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  display.display();

  digitalWrite(LED_PIN, HIGH);

  pinMode(KNOCK_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  resetGame();
  
  while(1) {
    getInput();
    player.update();
    bar.update(); bar2.update();
    drawLCD();
  }
}

void getInput() {
  int knock = digitalRead(KNOCK_PIN);
  if (knock == 0) { // push down
    clicked = true;
  } 
  else {
    clicked = false;
  }
}

void drawLCD() {
  display.clearDisplay();

  if (!player.isDead()) {
    int ht1 = bar.hitTest(player.getX(), player.getY());
    int ht2 = bar2.hitTest(player.getX(), player.getY());
    int die = ht1 + ht2;
    if (die == 1) {
        // game over
        player.die();
    }

    if (clicked) {
      player.flyUp();
    } 
    else {
      player.cancelJump();
    }
    player.render();	
    
    bar.render(); bar2.render(); 
  } 
  else {
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Game   Over!!!");
    if (clicked) {
      resetGame();
    }
  }

  display.display();
}

