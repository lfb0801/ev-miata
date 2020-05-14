#define leftPaddlePin 0
#define rightPaddlePin 1

char Gears[] = {'P', 'R', 'N', 'D', '2', '1'};
int selectedGear = 0;
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

void setup (void) {
  TimerStart ( & timerDisplay );
  timerDisplay = { 0, 3000 };

  Serial.begin(9600);
}

void loop (void) {
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

void taskDisplay ( void ) {
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

void shift ( struct PaddleState * paddles ) {
  if (paddles->right && paddles->left) {
    //  Both paddles pressed
    //  Maybe special action
  }
  if (!paddles->right && paddles->left) {
    Serial.println("Shifted up");
  }
  if (paddles->right && !paddles->left) {
    Serial.println("Shifted down");
  }
}

//  Timer Code

char TimerExpired ( struct Timer * timer ) {
  if ( millis () > timer->start + timer->timeout )
    return true;
  return false;
}

void TimerStart ( struct Timer * timer ) {
  timer->start = millis ( );
}
