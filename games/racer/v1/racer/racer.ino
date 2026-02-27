// Racer v1 - GameBoy (Arduino Nano)
// Початкова версія гри "Гонки"
// (результат 1-го уроку / початок 2-го )
// Малюємо машинки та керуємо  своєю машинкою

#include <GameBoy.h>

GameBoy gb;  

void setup() {

  gb.begin(10);
  playerCar(2, 12);
}

void loop() {
   if (gb.getKey() == 4) {
    clearPlayerCar(5, 12);
    playerCar(2, 12);
  } else if (gb.getKey() == 5) {
    clearPlayerCar(2, 12);
    playerCar(5, 12);
  }
}

void enemyCar(int x, int y) {
  gb.drawPoint(x, y);   
  gb.drawPoint(x, y - 1);
  gb.drawPoint(x - 1, y - 1);
  gb.drawPoint(x + 1, y - 1);
  gb.drawPoint(x, y - 2);    
  gb.drawPoint(x - 1, y - 3);
  gb.drawPoint(x + 1, y - 3);
}

void playerCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
}

void clearPlayerCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
}

void clearEnemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x, y - 2);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
}