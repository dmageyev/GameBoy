# GameBoy Arduino Library

Це Arduino-бібліотека для проєкту **GameBoy**.

## Структура

```
lib/GameBoy/
├── src/                 # Вихідний код бібліотеки
│   ├── GameBoy.h
│   ├── GameBoy.cpp
│   └── Blocks.h
├── examples/            # Приклади використання (Arduino IDE)
├── library.properties   # Метадані бібліотеки для Arduino IDE
├── keywords.txt         # Підсвітка ключових слів в Arduino IDE
└── .vscode/             # Налаштування для VS Code (опційно)
```

## Швидкий старт

### 1) Підключення

```cpp
#include <GameBoy.h>
```

### 2) Ініціалізація

Створіть обʼєкт `GameBoy` і викличте `begin()` у `setup()`.

```cpp
#include <GameBoy.h>

GameBoy gb;

void setup() {
  gb.begin(8);          // яскравість 0..15
  gb.clearDisplay();
}

void loop() {
}
```

> Примітка: у реалізації бібліотеки за замовчуванням використовуються піни `MOSI=12`, `CLK=11`, `CS=10`, а бузер — на піні `D4`.

## Основні можливості (API)

Нижче — короткий опис ключових методів класу `GameBoy` (див. `src/GameBoy.h`).

### Дисплей (матриця 8x16)

- `clearDisplay()` — очистити дисплей і внутрішню памʼять станів.
- `setLed(row, col, state)` — керування окремим світлодіодом.
  - `row`: 0..7
  - `col`: 0..15
  - `state`: `true/false`
- `drawPoint(x, y)` — увімкнути піксель без запису в памʼять.
- `memDisplay(x, y)` — записати точку у внутрішню памʼять `display[][]`.
- `wipePoint(x, y)` — вимкнути піксель і стерти його з памʼяті.
- `drawDisplay()` — перемалювати дисплей із внутрішньої памʼяті.

### Зіткнення / перевірки

- `checkCollision(x, y)` — перевірка колізії точки (або вихід за межі по Y).
- `isFree(x, y)` — чи вільна позиція (не зайнята і в межах поля).
- `checkBlockCollision(arr, x, y)` — колізія для блоку 4x4.

### Рух / гравітація / лінії

- `moveX(start_x, start_y, left_x, right_x, move_var)` — допоміжна логіка руху по X (залежить від `getKey()`).
- `fullLine()` — знаходить заповнені лінії, чистить їх і зсуває поле; повертає кількість очищених ліній.
- `clearLine(num_line)` — очистити конкретну лінію.

### Кнопки

- `getKey()` — повертає код натиснутої кнопки:
  - `1` — KEY1 (D2)
  - `2` — KEY2 (D3)
  - `3` — Up
  - `4` — Left
  - `5` — Right
  - `6` — Down

### Звук

- `sound(SCORE)` або `sound(COLLISION)` — програти короткий звук.

## Приклад: малюємо крапку і зберігаємо її в памʼять

```cpp
#include <GameBoy.h>

GameBoy gb;

void setup() {
  gb.begin(10);
  gb.clearDisplay();

  gb.memDisplay(3, 5);   // запамʼятати точку
  gb.drawDisplay();      // відмалювати з памʼяті

  gb.sound(SCORE);
}

void loop() {
}
```

## Файли

- `src/GameBoy.h`, `src/GameBoy.cpp` — основний інтерфейс та реалізація бібліотеки.
- `src/Blocks.h` — додаткові заголовки/константи.
- `library.properties` — метадані бібліотеки для Arduino IDE.
- `keywords.txt` — підсвітка ключових слів в Arduino IDE.
- `examples/` — приклади скетчів.

## Приклади

Див. каталог [`examples/`](examples/).