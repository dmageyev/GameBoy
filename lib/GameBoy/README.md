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

## Файли

- `src/GameBoy.h`, `src/GameBoy.cpp` — основний інтерфейс та реалізація бібліотеки.
- `src/Blocks.h` — додаткові заголовки/константи (залежно від використання у бібліотеці/іграх).
- `library.properties` — назва/версія/автор та інша інформація для Arduino Library Manager/IDE.
- `keywords.txt` — правила підсвітки в Arduino IDE.
- `examples/` — приклади скетчів для швидкого старту.

## Як підключити (Arduino IDE)

1. Скопіюйте папку `lib/GameBoy` у вашу папку бібліотек Arduino:
   - Windows: `Documents/Arduino/libraries/`
   - Linux: `~/Arduino/libraries/`
   - macOS: `~/Documents/Arduino/libraries/`
2. Перезапустіть Arduino IDE.
3. Підключайте бібліотеку у скетчі через `#include "GameBoy.h"` (файл знаходиться у `src/`).

## Приклади

Див. каталог [`examples/`](examples/).