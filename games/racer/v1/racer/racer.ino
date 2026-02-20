// Racer v1 - GameBoy (Arduino Nano)
// Початкова версія гри "Гонки"
// Малюємо машинки та керуємо  своєю машинкою

#include <GameBoy.h>

GameBoy gb;  // Об'єкт бібліотеки для роботи з матрицею 8x16 та кнопками

void setup() {
  // Ініціалізація дисплею, кнопок та інших периферійних пристроїв
  // Параметр 10 — яскравість (0..15)
  gb.begin(10);
  // Малюємо авто гравця на стартовій позиції
  playerCar(2, 12);
}

void loop() {
  // Arduino loop викликається нескінченно — запускаємо головний ігровий цикл
  // Обробка керування гравцем
  // getKey() повертає код кнопки:
  // 4 — Left, 5 — Right (за описом у бібліотеці)
  if (gb.getKey() == 4) {
    // Перемістити авто в ліву смугу:
    // спочатку стираємо авто у правій позиції, потім малюємо у лівій
    clearPlayerCar(5, 12);
    playerCar(2, 12);
  } else if (gb.getKey() == 5) {
    // Перемістити авто в праву смугу
    clearPlayerCar(2, 12);
    playerCar(5, 12);
  }
}

// Малює "ворожу" машину.
// (x, y) — опорна точка. Далі формується простий спрайт із 7 пікселів.
void enemyCar(int x, int y) {
  gb.drawPoint(x, y);          // низ (або "центр") авто
  gb.drawPoint(x, y - 1);      // середина
  gb.drawPoint(x - 1, y - 1);  // ліва частина
  gb.drawPoint(x + 1, y - 1);  // права частина
  gb.drawPoint(x, y - 2);      // "капот"
  gb.drawPoint(x - 1, y - 3);  // верх-ліво
  gb.drawPoint(x + 1, y - 3);  // верх-право
}

// Малює авто гравця.
// Тут спрайт зміщений "вниз" відносно опорної точки (y, y+1..y+3),
// щоб авто виглядало так, ніби воно стоїть внизу екрана.
void playerCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
}

// Стирає авто гравця в позиції (x, y) — ті ж самі точки, що і в playerCar().
void clearPlayerCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
}

// Стирає ворога в позиції (x, y) — ті ж самі точки, що і в enemyCar().
void clearEnemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x, y - 2);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
}