#include <LiquidCrystal_I2C.h>
#include <Wire.h>

/***********************/
/*        DISPLAY      */
/***********************/
LiquidCrystal_I2C lcd(0x27, 16, 2);

/***********************/
/*        PINS         */
/***********************/
// Matrix
// Output Pins
const int PO_[4] = {22, 23, 50, 48};
// Input Pins
const int PI_[16] = {25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 52};

/***********************/
/*        VARIABLES    */
/***********************/
// Matrix Values
const String MATRIX_VALUES[4][16] = {
    {"Double 12", "Single 12", "Double 9", "Single 9", "Double 14", "Single 14", "Double 11", "Single 11", "Double 8", "Single 8", "N/A", "Triple 12", "Triple 9", "Triple 14", "Triple 11", "Triple 8"},
    {"Double 16", "Single 16", "Double 7", "Single 7", "Double 19", "Single 19", "Double 3", "Single 3", "Double 17", "Single 17", "Double 25", "Triple 16", "Triple 7", "Triple 19", "Triple 3", "Triple 17"},
    {"Double 2", "Single 2", "Double 15", "Single 15", "Double 10", "Single 10", "Double 6", "Single 6", "Double 13", "Single 13", "Single 25", "Triple 2", "Triple 15", "Triple 10", "Triple 6", "Triple 13"},
    {"Double 4", "Single 4", "Double 18", "Single 18", "Double 1", "Single 1", "Double 20", "Single 20", "Double 5", "Single 5", "N/A", "Triple 4", "Triple 18", "Triple 1", "Triple 20", "Triple 5"}};

bool bI[4][16];
bool bHitOnce = false;

// (C)
byte copyright[8] = {
  B11111,
  B10001,
  B10101,
  B10111,
  B10101,
  B10001,
  B11111,
  B00000
};


/***********************/
/*       Functions     */
/***********************/
/* Display the hit on LCD */
void DisplayHit(String hit)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hit detected:");
  lcd.setCursor(0,1);
  lcd.print(hit);
}

void EvalThrow()
{ 
  for (int x = 0; x < 4; x++)
  {
    digitalWrite(PO_[0], HIGH);
    digitalWrite(PO_[1], HIGH);
    digitalWrite(PO_[2], HIGH);
    digitalWrite(PO_[3], HIGH);
    digitalWrite(PO_[x], LOW);

    for (int y = 0; y < 16; y++)
    {
      bI[x][y] = digitalRead(PI_[y]);
      if (bI[x][y] == 0)
      {
        bHitOnce = true;        
        DisplayHit(MATRIX_VALUES[x][y]);
        delay(300);        
        // Set Bull to 0
        bI[1][10] = 1;
        bI[2][10] = 1;
      }
    }
  }
}

/* Display intro on LCD */
void DisplayIntro()
{
  // print verion info
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Matrix Tester v1");
  lcd.createChar(0, copyright);
  lcd.setCursor(0,1);
  lcd.write((byte)0);
  lcd.print(" Patrick Hener");
  delay(5000);
  // print welcome message
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Plugin in");
  lcd.setCursor(0,1);
  lcd.print("matrix and test");  
  delay(5000);
}

/* Setup loop */
void setup()
{
  // Matrix
  for (int i = 0; i < 4; i++)
  {
    pinMode(PO_[i], OUTPUT);
  }

  for (int i = 0; i < 16; i++)
  {
    pinMode(PI_[i], INPUT_PULLUP);
  }

  // initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
 

  // Start serial
  Serial.begin(9600);
}


/* Main loop */
void loop()
{ 
  if (!bHitOnce) {
    DisplayIntro();
  }
  
  EvalThrow();
}
