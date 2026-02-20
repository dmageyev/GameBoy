# GameBoy

Розробка відео-ігор для плати GameBoy на базі Arduino Nano.

## Структура проекту

```
GameBoy/
├── lib/                    # Бібліотеки Arduino
├── games/                  # Ігри
│   ├── snake/              # Змійка
│   │   ├── v1/             # Версія 1
│   │   └── README.md
│   ├── tetris/             # Тетріс
│   │   ├── v1/
│   │   └── README.md
│   ├── racer/              # Гонки
│   │   ├── v1/racer/
|   |   |   └── racer.ino
│   │   ├── v2/racer/
|   |   |   └── racer.ino
│   │   └── README.md
│   └── platformer/         # Платформер
│       ├── v1/
│       └── README.md
└── system/                 # Єдина система з головним меню
    ├── v1/
    └── README.md
```

## Ігри

| Гра                    | Каталог                                          |
|------------------------|--------------------------------------------------|
| Гонки                  | [`games/racer/`](games/racer/README.md)          |
| Тетріс                 | [`games/tetris/`](games/tetris/README.md)        |
| Змійка                 | [`games/snake/`](games/snake/README.md)          |
| Платформер             | [`games/platformer/`](games/platformer/README.md)|

## Версіонування

Кожна гра та системний модуль мають власні підкаталоги версій (`v1/`, `v2/`, …), що дозволяє фіксувати етапи розробки та легко повертатися до попередніх реалізацій.

## Бібліотеки

Усі Arduino-бібліотеки, необхідні для проекту, зберігаються у каталозі [`lib/`](lib/README.md).
