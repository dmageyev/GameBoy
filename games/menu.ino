#include <GameBoy.h>

GameBoy gb;

byte ARROWS[8][8] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 1, 1, 1, 0, 0, 1, 1, 1 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};


byte CAR[8][8] = {
  { 0, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0 }
};

byte SNAKE[8][8] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 }
};

int modeCount = 0;

int snakeX[10];
int snakeY[10];

int up     = 0;
int right  = 1;
int bottom = 2;
int left   = 3;
int direction = right;

int eatX, eatY;

bool state;

int lenSnake = 7;
const int numRows = 8;
const int numCols = 16;
void setup() {
  gb.begin(0);
  snakeX[0] = 4;
  snakeY[0] = 7;
  randomSeed(analogRead(2));
  makeFruit();
}

void makeMove() {
  if (gb.getKey() == 4 && direction != right) {
    direction = left;
  }
  if (gb.getKey() == 5 && direction != left) {
    direction = right;
  }
  if (gb.getKey() == 6 && direction != up) {
    direction = bottom;
  }
  if (gb.getKey() == 3 && direction != bottom) {
    direction = up;
  }
}

void move() {
  if ((snakeX[0] == eatX) and (snakeY[0] == eatY)) {
    lenSnake++;
    makeFruit();
    gb.sound(SCORE);
  }
  for (int i = lenSnake - 1; i > 0; i--) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gb.sound(COLLISION);
      loss();
    }
  }
  for (int i = lenSnake - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  if (direction == up) {
    if (snakeY[0] == 0) {
      snakeY[0] = 15;
    } else {
      snakeY[0]--;
    }
  } else if (direction == bottom) {
    if (snakeY[0] == 15) {
      snakeY[0] = 0;
    } else {
      snakeY[0]++;
    }
  } else if (direction == left) {
    if (snakeX[0] == 0) {
      snakeX[0] = 7;
    } else {
      snakeX[0]--;
    }
  } else if (direction == right) {
    if (snakeX[0] == 7) {
      snakeX[0] = 0;
    } else {
      snakeX[0]++;
    }
  }
}

void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
  }
}

void drawFruit() {
  state = !state;
  if ( state == true) {
    gb.drawPoint(eatX, eatY);
  }
  else {
    gb.wipePoint(eatX, eatY);
  }
}
boolean isPartOfSnake(int x, int y) {
  for (int i = 0; i < lenSnake - 1; i++) {
    if ((x == snakeX[i]) && (y == snakeY[i])) {
      return true;
    }
  }
  return false;
}

void makeFruit() {
  eatX = random(0, 8);
  eatY = random(0, 16);
  while (isPartOfSnake(eatX, eatY)) {

    eatX = random(0, 8);
    eatY = random(0, 16);
  }
}

void loss() {
  delay(1000);
  gb.clearDisplay();
  for (int i = 0; i < lenSnake; i++) {
    snakeX[i] = 0;
    snakeY[i] = 0;
  }
  direction = right;
  eatX = 3;
  eatY = 3;
  lenSnake = 4;
  snakeX[0] = 4;
  snakeY[0] = 7;
}

void gameSnake() {
  makeMove();
  move();
  gb.clearDisplay();
  drawSnake();
  drawFruit();
  delay(250);
}

void loop() {
  mainMenu();
}



void mainMenu() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j);
      gb.setLed(i, j, ARROWS[j][i]);
    }
  }
if (modeSelector() == 0) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j +8);
      gb.setLed(i, j +8, CAR[j][i]);
    }
  }
}
if (modeSelector() == 1) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j +8);
      gb.setLed(i, j +8, SNAKE[j][i]);
    }
  }
}

}


int modeSelector() {
  if (gb.getKey() == 4) {
    modeCount++;
    delay(250);
    if (modeCount > 1) {
      modeCount = 0;
    }
  } else if (gb.getKey() == 5) {
    modeCount--;
    delay(250);
    if (modeCount < 0) {
      modeCount = 1;
    }
  }
  return modeCount;
}

