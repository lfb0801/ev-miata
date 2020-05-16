#define leftPaddlePin 11
#define rightPaddlePin 12

char Gears[] = {'P', 'R', 'N', 'L', 'H'};
int currentGear;
bool shifting = false;

struct Timer {
  unsigned long start;
  unsigned long timeout;
};

struct PaddleState {
  bool right;
  bool left;
};

PaddleState currentPaddles;
PaddleState lastPaddles;
Timer timerDisplay;

void setup() {
  TimerStart ( & timerDisplay );
  timerDisplay = { 0, 3000 };

  currentGear = 0;

  pinMode(leftPaddlePin, INPUT);
  pinMode(rightPaddlePin, INPUT);

  Serial.begin(9600);
}

void loop() {
  //  Read shifters
  currentPaddles = { digitalRead(leftPaddlePin), digitalRead(rightPaddlePin) };

  if ( TimerExpired ( & timerDisplay ) ) {
    taskDisplay ( );
    TimerStart ( & timerDisplay );
  }

  if (comparePaddles(&currentPaddles, &lastPaddles)) {
    if ( !shifting ) {
      shift( & currentPaddles );
    }
    delay(50); // Delay a little bit to avoid bouncing
  }
  lastPaddles = currentPaddles;
}

//  Display Code

void taskDisplay() {
  //  Display Gears[selectedGear]
}

//  Shifter Code

bool comparePaddles(struct PaddleState * p0, struct PaddleState * p1) {
  bool o = true;
  if (p0->right != p1->right) {
    o = false;
  }
  if (p0->left != p1->left) {
    o = false;
  }
}

/*
   Shifting cycle N>L>H
   Shifting down H>L>N>R
   Shifting up R>L
   Double Paddle cycle(P > N > P)
*/
void shift(struct PaddleState * paddles) {
  if (paddles->left && paddles->right) {
    switch (currentGear) {
      case 0:
        //  code to use shifter
        //  wait for callback
        //  when its in gear
        currentGear = 1;
        break;
      case 1:
        //  code to use shifter
        //  wait for callback
        //  when its in gear
        currentGear = 0;
        break;
      default:
        /* MAYBE:
           add possibility to switch from any gear to Neutral with this combination
           if (speed < 5.0){ currentGear = 'N' }
        */
        break;
    }
  }
  if (!paddles->left && paddles->right) {
    switch (currentGear) {
      case 0:
        //  Display error?: GEAR IS LOCKED
        break;
      case 4:
        //  Display error?: THERE IS NO HIGHER GEAR
        break;
      default:
        //  code to use shifter
        //  wait for callback
        //  when its in gear
        currentGear += 1;
        break;
    }
  }
  if (paddles->left && !paddles->right) {
    switch (currentGear) {
      case 0:
        //  Display error?: GEAR IS LOCKED
        break;
      case 1:
        //  Display error?: THERE IS NO LOWER GEAR
        break;
      default:
        //  code to use shifter
        //  wait for callback
        //  when its in gear
        currentGear -= 1;
        break;
    }
  }
}

//  Timer Code

char TimerExpired(struct Timer * timer) {
  if ( millis () > timer->start + timer->timeout )
    return true;
  return false;
}

void TimerStart(struct Timer * timer) {
  timer->start = millis ( );
}
