#include <Arduino.h>

//TODO: rewrite timer. 
//note: millis() is like a wall clock that doesn't stop.

const int homeGoal = 2;
const int visitorGoal = 3;
const int gameMode = 4;
const int pauseButton = 5;
const int startButton = 6;
const int addButton = 7;
const int subtractButton = 8;
const int resetButton = 9;

int homescore;
int visitorscore; 

int defaultWinScore;
int winScore;

int defaultgametime = 10;
int gametime = defaultgametime;
int timebuttonchange = 60;

int isPaused = 1;

unsigned long lastpause;
unsigned long laststart;
unsigned long lastPauseDuration;
unsigned long roughGameLength;
unsigned long totalGamePauseTime;
unsigned long netGameLength;
unsigned long gameStartTime;

bool pause = true;


void setup() 
{
  Serial.begin(9600);
  int homescore;
  int visitorscore;

  pinMode(homeGoal, INPUT);
  pinMode(visitorGoal, INPUT); 
  pinMode(pauseButton, INPUT);
  pinMode(startButton, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(gameMode, INPUT_PULLUP);
  Serial.println("on");

}

void startStop()
{
  int pausebuttonstatus = digitalRead(pauseButton);
  int startbuttonstatus = digitalRead(startButton);

  if(pausebuttonstatus = LOW)
  {
    bool pause = true;
  }

  else if(startbuttonstatus = LOW)
  {
    bool pause = false;
  } 
}

void resetgame()
{
  homescore = 0;
  visitorscore = 0;

  roughGameLength = 0;
  totalGamePauseTime = 0;
  netGameLength = 0;

  pause = true;
  isPaused = 1;
  
  gameStartTime = millis();
  lastpause = gameStartTime;
  Serial.println("Game reset.");
}

void timedgame()
{
  if(pause = true)
  {
    if(isPaused = 0)
    {
      lastpause = millis();
      isPaused = 1;
    }
  }

  else if(pause = false)
  {
    if(isPaused = 1)
    {
      laststart = millis();
      isPaused = 0;
      
      lastPauseDuration = laststart - lastpause;
      totalGamePauseTime = totalGamePauseTime + lastPauseDuration;
    }

    if(digitalRead(homeGoal) == LOW)
    {
      homescore = homescore + 1;
    }
    else if(digitalRead(visitorGoal) == LOW)
    {
      visitorscore = visitorscore + 1;
    }
  }

  if(digitalRead(addButton) == LOW)
  {
    gametime + timebuttonchange;
  }
  
  if(digitalRead(subtractButton) == LOW)
  {
    gametime - timebuttonchange;
  }

  if(resetButton == LOW)
  {
    resetgame();
  }
}

void scoredgame()
{
  if(pause = true)
  {
    if(isPaused = 0)
    {
      lastpause = millis();
      isPaused = 1;
    }
  }

  else if(pause = false)
  {
    if(isPaused = 1)
    {
      laststart = millis();
      isPaused = 0;
      
      lastPauseDuration = laststart - lastpause;
    }

    if(digitalRead(homeGoal) == LOW)
    {
      homescore = homescore + 1;
    }
    
    else if(digitalRead(visitorGoal) == LOW)
    {
      visitorscore = visitorscore + 1;
    }
  }

  if(digitalRead(addButton) == LOW)
  {
    ++winScore;
  }
    
  if(digitalRead(subtractButton) == LOW)
  {
    --winScore;
  }

  if(resetButton == LOW)
  {
    resetgame();
  }
}

void loop() 
{
  if (digitalRead(gameMode) == LOW)
  {
    while((homescore < winScore) && (visitorscore < winScore))
    {
      scoredgame();
    }
    
    if(homescore > winScore)
    {
      //home won
    }
    else if(visitorscore > winScore)
    {
      //visitor won
    }
  }
  else if (digitalRead(gameMode) == HIGH)
  {
    while(millis() - totalGamePauseTime - gameStartTime / 1000 < gametime)
    {
      timedgame();
    }
    
    if(homescore > visitorscore)
    {
      //home won
    }
    else if(visitorscore > homescore)
    {
      //visitor won
    }
    else
    {
      Serial.println("Jack wins.");
    }
  }
}