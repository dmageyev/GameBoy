// Racer final - GameBoy (Arduino Nano)
// Фінальна версія гри "Гонки"
// кінець 3-го (використовується пізніше при створенні меню)
// Додано зіткнення, звук та закінчення гри

#include <GameBoy.h>

GameBoy gb;  

int enemy_x = 2;
int car_speed = 100;
int mycar_x = 2;
int mycar_y = 12;

void setup() {
  gb.begin(10);
  playerCar(mycar_x, mycar_y);
  randomSeed(analogRead(0));
}

void loop() {
  mainRaicing();
}

void mainRaicing() {
  enemy_x = random(0, 10);
  if (enemy_x > 5) enemy_x = 2;
  else enemy_x = 5;

  for (int enemy_y = 0; enemy_y < 16; enemy_y++) {
    enemyCar(enemy_x, enemy_y);

    createLine(enemy_y);
    createLine(enemy_y + 5);
    createLine(enemy_y + 10);
    createLine(enemy_y + 15);
    createLine(enemy_y - 5);
    createLine(enemy_y - 10);
    createLine(enemy_y - 15);

    if (gb.getKey() == 4) {
      clearPlayerCar(5, 12);
      mycar_x = 2;
    } else if (gb.getKey() == 5) {
      clearPlayerCar(2, 12);
      mycar_x = 5;
    }
    playerCar(mycar_x, mycar_y);

    if (Collision(mycar_x, mycar_y, enemy_x, enemy_y)) {
      gb.sound(COLLISION);
      gb.testMatrix(10);
      gb.clearDisplay();
      return;
    }
    if (enemy_y>14)
      gb.sound(SCORE);

    delay(car_speed);

    clearEnemyCar(enemy_x, enemy_y);

    clearLine(enemy_y);
    clearLine(enemy_y + 5);
    clearLine(enemy_y + 10);
    clearLine(enemy_y + 15);
    clearLine(enemy_y - 5);
    clearLine(enemy_y - 10);
    clearLine(enemy_y - 15);
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

void createLine(int y) {
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);

  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}

void clearLine(int y) {
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);

  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}

bool Collision(int p_x, int p_y, int e_x, int e_y) {
  if (p_x == e_x && p_y <= e_y) return true;
  return false;
}
