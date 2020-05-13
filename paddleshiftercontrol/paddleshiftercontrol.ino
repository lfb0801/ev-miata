#define leftPaddlePin 0
#define rightPaddlePin 1

char Gears[] = {'P', 'R', 'N', 'D', '2', '1'};
int selectedGear = 0;
bool shifting = false;

typedef struct Timer {
  unsigned long start;
  unsigned long timeout;
};

typedef struct PaddleState {
  bool right;
  bool left;
};

//Display task running every 3000 milliseconds
Timer timerDisplay = { 0, 3000 };

void setup (void) {
  TimerStart ( & timerDisplay );
}

void loop (void) {
  //  Read shifters
  PaddleState paddles = { digitalRead(leftPaddlePin), digitalRead(rightPaddlePin) };

  if ( !shifting ) {
    shift( & paddles );
  }
  if ( TimerExpired ( & timerDisplay ) ) {
    taskDisplay ( );
    TimerStart ( & timerDisplay );
  }
}

void shift ( struct PaddleState * paddles ) {
  if (paddels->right && paddels->left) {
    //  Both paddles pressed
    //  Maybe special action
  }
  if (!paddels->right && paddels->left){}
  if (paddels->right && !paddels->left){}
  }

void taskDisplay ( void ) {
  //  Display Gears[selectedGear]
}

char TimerExpired ( struct Timer * timer ) {
  if ( millis () > timer->start + timer->timeout )
    return true;
  return false;
}

void TimerStart ( struct Timer * timer ) {
  timer->start = millis ( );
}
