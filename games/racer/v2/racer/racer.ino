// Racer v2 - GameBoy (Arduino Nano)
// Наступна версія гри "Гонки"
// Додано появу ворога та імітацію руху ворога та дороги

#include <GameBoy.h>

GameBoy gb;              // Об'єкт бібліотеки для роботи з матрицею 8x16 та кнопками

// Позиція ворога по X (ліва або права смуга)
int enemy_x = 2;

// Швидкість гри (затримка між кадрами). Менше значення -> швидше рухається.
int car_speed = 100;

// Позиція машини гравця (X та Y). Y майже внизу екрана.
int mycar_x = 2;
int mycar_y = 12;

void setup() {
  // Ініціалізація дисплею, кнопок та інших периферійних пристроїв
  // Параметр 10 — яскравість (0..15)
  gb.begin(10);

  // Малюємо авто гравця на стартовій позиції
  playerCar(mycar_x, mycar_y);

  // Ініціалізуємо генератор випадкових чисел "шумом" з аналогового піну
  randomSeed(analogRead(0));
}

void loop() {
  // Arduino loop викликається нескінченно — запускаємо головний ігровий цикл
  mainRaicing();
}

void mainRaicing() {
  // Основний ігровий цикл
  // Тут ворог "спавниться" у випадковій смузі, та рухається зверху вниз.

  // Випадково обираємо значення (0..9). Далі зводимо це до однієї з двох смуг.
  enemy_x = random(0, 10);

  // Приводимо випадкове значення до двох можливих X:
  // якщо більше 5 — ворог буде в лівій смузі (x=2), інакше — в правій (x=5)
  if (enemy_x > 5) enemy_x = 2;
  else enemy_x = 5;

  // Рухаємось по Y: ворог "падає" зверху (0) донизу (15)
  for (int enemy_y = 0; enemy_y < 16; enemy_y++) {

    // 1) Малюємо ворога на поточній висоті
    enemyCar(enemy_x, enemy_y);

    // 2) Малюємо "дорогу" — вертикальні лінії зліва і справа.
    // Щоб створити ілюзію руху, малюємо кілька сегментів зміщених по Y.
    // Частина координат може бути поза екраном — бібліотека просто не намалює/обріже.
    createLine(enemy_y);
    createLine(enemy_y + 5);
    createLine(enemy_y + 10);
    createLine(enemy_y + 15);
    createLine(enemy_y - 5);
    createLine(enemy_y - 10);
    createLine(enemy_y - 15);

    // 3) Обробка керування гравцем
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

    // 4) Затримка між кадрами (швидкість гри)
    delay(car_speed);

    // 5) Очистка кадру: прибираємо ворога та дорогу на поточних координатах
    // щоб на наступній ітерації намалювати їх нижче.
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

// Малює сегмент "лінії дороги" на лівому (x=0) та правому (x=7) краях.
// Фактично це 3 пікселі по вертикалі на кожному краї.
void createLine(int y) {
  // Лівий край
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);

  // Правий край
  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}

// Стирає сегмент "лінії дороги" (аналогічно createLine()).
void clearLine(int y) {
  // Лівий край
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);

  // Правий край
  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}