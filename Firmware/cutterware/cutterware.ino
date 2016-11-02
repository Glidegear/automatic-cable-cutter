#include <AccelStepper.h>
#include <LiquidCrystal.h>
#include <QuadEncoder.h>

#define X_STEP_PIN          54
#define X_DIR_PIN           55
#define X_ENABLE_PIN        38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define BEEPER             37

#define BTN_EN1 31
#define BTN_EN2 33
#define BTN_ENC 35
QuadEncoder encoder(BTN_EN1,BTN_EN2); // initialize the encoder

#define KILL_PIN 41

#define LCD_PINS_RS 16 //[RAMPS14-SMART-ADAPTER]
#define LCD_PINS_ENABLE 17 //[RAMPS14-SMART-ADAPTER]
#define LCD_PINS_D4 23 //[RAMPS14-SMART-ADAPTER]
#define LCD_PINS_D5 25 //[RAMPS14-SMART-ADAPTER]
#define LCD_PINS_D6 27 //[RAMPS14-SMART-ADAPTER]
#define LCD_PINS_D7 29 //[RAMPS14-SMART-ADAPTER]         

LiquidCrystal lcd(LCD_PINS_RS, LCD_PINS_ENABLE, LCD_PINS_D4, LCD_PINS_D5,LCD_PINS_D6,LCD_PINS_D7);  //RS,Enable,D4,D5,D6,D7

AccelStepper stepper(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperForward(1, Y_STEP_PIN, Y_DIR_PIN);
//#define stepPin 54
//#define dirPin 55
//#define enablePin 38


/*
REQUIRED GLOBAL VARIABLES & DEFINITIONS
 */
#define MOVECURSOR 1  // constants for indicating whether cursor should be redrawn
#define MOVELIST 2  // constants for indicating whether cursor should be redrawn
byte totalRows = 1;  // total rows of LCD
byte totalCols = 20;  // total columns of LCD
unsigned long timeoutTime = 0;  // this is set and compared to millis to see when the user last did something.
const int menuTimeout = 10000; // time to timeout in a menu when user doesn't do anything.


unsigned int length = 0;
unsigned int pcs = 1;


// has the encoder moved on this loop?
boolean moved = false;

void setup()
{
  pinMode(BTN_ENC,INPUT);
  digitalWrite(BTN_ENC,HIGH);
  // We set the enable pin to be an output
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  // then we set it HIGH so that the board is disabled until we
  // get into a known state.
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);  
  Serial.begin(9600);



  //pinMode(stepPin, OUTPUT);
  //pinMode(dirPin, OUTPUT);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(10000.0);
  stepperForward.setMaxSpeed(4000);
  stepperForward.setAcceleration(10000.0);

}
void loop()
{
  //int j;
  // set the enablePin low so that we can now use our stepper driver.
//digitalWrite(X_ENABLE_PIN, LOW);
//digitalWrite(Y_ENABLE_PIN, LOW);
  //stepper.moveTo(2000); 
  //stepper.setSpeed(500);
  //stepper.runSpeedToPosition();
  //stepper.run();
  //stepper.move(-10);
  //stepper.run();
//cut();


    //if (stepper.distanceToGo() == 0)
    //{
	// Random change to speed, position and acceleration
	// Make sure we dont get 0 speed or accelerations
	//delay(1000);
	//stepper.moveTo(rand() % 200);
	//stepper.setMaxSpeed((rand() % 20000) + 1);
	//stepper.setAcceleration((rand() % 2000) + 1);
    //}
    //stepper.run();
    
  basicMenu();
  //lcd.print("hello, world!");





  // we set the direction pin in an arbitrary direction.
  //digitalWrite(dirPin, HIGH);
  //for(j=0; j<=10000; j++) {
  //digitalWrite(stepPin, LOW);
  //delayMicroseconds(2);
  //digitalWrite(stepPin, HIGH);
  //delayMicroseconds(1000);
}


/*
MENU ROUTINE
 */
void basicMenu(){

  byte topItemDisplayed = 0;  // stores menu item displayed at top of LCD screen
  byte cursorPosition = 0;  // where cursor is on screen, from 0 --> totalRows. 

  // redraw = 0  - don't redraw
  // redraw = 1 - redraw cursor
  // redraw = 2 - redraw list
  byte redraw = MOVELIST;  // triggers whether menu is redrawn after cursor move.
  byte i=0; // temp variable for loops.
  byte totalMenuItems = 0;  //a while loop below will set this to the # of menu items.

  // Put the menu items here. Remember, the first item will have a 'position' of 0.
  char* menuItems[]={

 
    "Length mm x 100",
    "Length mm x 10",
    "Length mm",
    "Pieces",
    "Start",
    "Manual Move",
    "Manual Cut",
    "",
  };

  while (menuItems[totalMenuItems] != ""){
    totalMenuItems++;  // count how many items are in list.
  }
  totalMenuItems--;  //subtract 1 so we know total items in array.

  lcd.clear();  // clear the screen so we can paint the menu.

  boolean stillSelecting = true;  // set because user is still selecting.

  timeoutTime = millis() + menuTimeout; // set initial timeout limit. 

  do   // loop while waiting for user to select.
  {

    /*
    IF YOU WANT OTHER CODE GOING ON IN THE BACKGROUND
     WHILE WAITING FOR THE USER TO DO SOMETHING, PUT IT HERE
     */

    /*
    my code uses a rotary encoder for input. 
     You should obviously change the code to meet your needs.
     For a button, you could do something like this, but note that
     it does not have ANY debouncing and will scroll for as long as
     the button is being pushed. This is not a button tutorial, 
     so you should look elsewhere on how to implement that. Just 
     remember that ALL of the code between the corresponding 'case'
     and 'break' should be moved to each button push routine.
     
     
     buttonState = digitalRead(buttonPin);
     if (buttonState == HIGH) {     
     AND THEN PUT THE CORRESPONDING CODE
     FROM BELOW HERE
     } 
     */
    switch(readEncoder()) 
    {  // analyze encoder response. Default is 0.


    case 1:  // ENCODER ROTATED UP. EQUIVALENT OF 'UP' BUTTON PUSHED
      Serial.println("ENCODE REDADA. c1");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      //  if cursor is at top and menu is NOT at top
      //  move menu up one.
      if(cursorPosition == 0 && topItemDisplayed > 0)  //  Cursor is at top of LCD, and there are higher menu items still to be displayed.
      {
        topItemDisplayed--;  // move top menu item displayed up one. 
        redraw = MOVELIST;  // redraw the entire menu
      }

      // if cursor not at top, move it up one.
      if(cursorPosition>0)
      {
        cursorPosition--;  // move cursor up one.
        redraw = MOVECURSOR;  // redraw just cursor.
      }
      break;

    case 2:    // ENCODER ROTATED UP. EQUIVALENT OF 'DOWN' BUTTON PUSHED
      Serial.println("ENCODE REDADA. c2");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      // this sees if there are menu items below the bottom of the LCD screen & sees if cursor is at bottom of LCD 
      if((topItemDisplayed + (totalRows-1)) < totalMenuItems && cursorPosition == (totalRows-1))
      {
        topItemDisplayed++;  // move menu down one
        redraw = MOVELIST;  // redraw entire menu
      }
      if(cursorPosition<(totalRows-1))  // cursor is not at bottom of LCD, so move it down one.
      {
        cursorPosition++;  // move cursor down one
        redraw = MOVECURSOR;  // redraw just cursor.
      }
      break;

    case 4:  // ENCODER BUTTON PUSHED FOR SHORT PERIOD & RELEASED.
      // EQUIVALENT TO 'SELECT' OR 'OKAY' BEING PUSHED       
      Serial.println("ENCODE REDADA. c4");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      Serial.println("eee" + topItemDisplayed + cursorPosition);
      switch(topItemDisplayed + cursorPosition) // adding these values together = where on menuItems cursor is.
      {
        //  put code to be run when specific item is selected in place of the Serial.print filler.
        // the Serial.print code can be removed, but DO NOT change the case & break structure. 
        // (Obviously, you should have as many case instances as you do menu items.)
      case 0:  // menu item 1 selected
        lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
        lcd.print(">");
        //stillSelecting = true;
        getRotarylength(100);
        Serial.print( pcs + topItemDisplayed + cursorPosition);
        Serial.print(" selected - ");
        Serial.println(menuItems[topItemDisplayed + cursorPosition]);
        // there is no menuSubMenu1() function. BUT, to have nested menus,
        // copy this function(i.e. all of basicMenu) into a new function named 
        // whatever you want for your sub menu items and repeat.
        //        menuSubMenu1();
        break;
      case 1:  // menu item 1 selected
        lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
        lcd.print(">");
        //stillSelecting = true;
        getRotarylength(10);
        Serial.print( pcs + topItemDisplayed + cursorPosition);
        Serial.print(" selected - ");
        Serial.println(menuItems[topItemDisplayed + cursorPosition]);
        // there is no menuSubMenu1() function. BUT, to have nested menus,
        // copy this function(i.e. all of basicMenu) into a new function named 
        // whatever you want for your sub menu items and repeat.
        //        menuSubMenu1();
        break;
      case 2:  // menu item 1 selected
        lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
        lcd.print(">");
        //stillSelecting = true;
        getRotarylength(1);
        Serial.print( pcs + topItemDisplayed + cursorPosition);
        Serial.print(" selected - ");
        Serial.println(menuItems[topItemDisplayed + cursorPosition]);
        // there is no menuSubMenu1() function. BUT, to have nested menus,
        // copy this function(i.e. all of basicMenu) into a new function named 
        // whatever you want for your sub menu items and repeat.
        //        menuSubMenu1();
        break;        
      case 3:  // menu item 2 selected
         lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
         lcd.print(">");
        //stillSelecting = true;
        getRotarypcs();
        
        Serial.print("Menu item ");
        Serial.print(topItemDisplayed + cursorPosition);
        Serial.print(" selected - ");
        Serial.println(menuItems[topItemDisplayed + cursorPosition]);
        break;

      case 4:  // menu item 3 selected
        lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
         lcd.print(">");
         start();
        Serial.print("will make: " + pcs);
        Serial.print("mm: " + length);
        Serial.print(topItemDisplayed + cursorPosition);
        Serial.print(" selected - ");
        Serial.println(menuItems[topItemDisplayed + cursorPosition]);
        break;

      case 5:  // menu item 4 selected
         lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
         lcd.print(">");
        Serial.print("Manual Move");
        getRotaryMove();   
        Serial.print("Menu item ");
        Serial.print(topItemDisplayed + cursorPosition);
        Serial.print(" selected - ");
        Serial.println(menuItems[topItemDisplayed + cursorPosition]);
        break;
        
      case 6:  // menu item 4 selected
        Serial.print("Manual cut");
        lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
        lcd.print(">");
        cut();      
        Serial.print("Menu item ");
        Serial.print(topItemDisplayed + cursorPosition);
        Serial.print(" selected - ");
        Serial.println(menuItems[topItemDisplayed + cursorPosition]);
        break;        

  

        // add as many "case #:" as items you have. You could put 
        //  line separators in menuList and leave out the 
        //  corresponding case, which would mean that nothing
        // would be triggered when user selected the line separator.  
      }
      break;

    case 8:  // encoder button was pushed for long time. This corresponds to "Back" or "Cancel" being pushed.
      stillSelecting = false;
      Serial.println("Button held for a long time");
      break;

    }

    switch(redraw){  //  checks if menu should be redrawn at all.
    case MOVECURSOR:  // Only the cursor needs to be moved.
      redraw = false;  // reset flag.
      if (cursorPosition > totalMenuItems) // keeps cursor from moving beyond menu items.
        cursorPosition = totalMenuItems;
      for(i = 0; i < (totalRows); i++){  // loop through all of the lines on the LCD
        lcd.setCursor(0,i);
        lcd.print(" ");                      // and erase the previously displayed cursor
        lcd.setCursor((totalCols-1), i);
        lcd.print(" ");
      }
      lcd.setCursor(0,cursorPosition);      // go to LCD line where new cursor should be & display it.
      lcd.print(">");
      lcd.setCursor((totalCols-1), cursorPosition);
      lcd.print("<");
       lcd.setCursor(22,2);
      Serial.print(length);
      lcd.print("mm: " + String(length));
      lcd.setCursor(32,2);
      lcd.print(String(pcs) + "pcs.");
      break;  // MOVECURSOR break.

    case MOVELIST:  // the entire menu needs to be redrawn
      redraw=MOVECURSOR;  // redraw cursor after clearing LCD and printing menu.
      lcd.clear(); // clear screen so it can be repainted.
      if(totalMenuItems>((totalRows-1))){  // if there are more menu items than LCD rows, then cycle through menu items.
        for (i = 0; i < (totalRows); i++){
          lcd.setCursor(1,i);
          lcd.print(menuItems[topItemDisplayed + i]);
        }
      }
      else{  // if menu has less items than LCD rows, display all available menu items.
        for (i = 0; i < totalMenuItems+1; i++){
          lcd.setCursor(1,i);
          lcd.print(menuItems[topItemDisplayed + i]);
        }
      }
      break;  // MOVELIST break
    }

    if (timeoutTime<millis()){  // user hasn't done anything in awhile
      stillSelecting = false;  // tell loop to bail out.
      /*
      in my main code, I had a function that
       displayed a default screen on the LCD, so
       I would put that function here, and it would
       bail out to the default screen.
       defaultScreen();
       */
    }
  } 


  while (stillSelecting == true);  //
}

void start() {
     cut();
     //digitalWrite(X_ENABLE_PIN, LOW);
     digitalWrite(Y_ENABLE_PIN, LOW);
     // wait a few microseconds for the enable to take effect
     // (That isn't in the spec sheet I just added it for sanity.)
     delayMicroseconds(2);  
  for (int i=1; i <= pcs; i++){
       //stepper.setSpeed(500);
       stepperForward.runToNewPosition((i* length )*30.3);
       //stepperForward.run();
      cut();
   } 
   stepperForward.setCurrentPosition(0);
        //digitalWrite(X_ENABLE_PIN, HIGH);
     digitalWrite(Y_ENABLE_PIN, HIGH);
     tone(BEEPER, 65,200);
     delay(200);
     tone(BEEPER, 196,200);  
     delay(200);
     tone(BEEPER, 262,200);    
}


void cut(){
  // set the enablePin low so that we can now use our stepper driver.
digitalWrite(X_ENABLE_PIN, LOW);
// wait a few microseconds for the enable to take effect
// (That isn't in the spec sheet I just added it for sanity.)
delayMicroseconds(2);
stepper.setSpeed(1000);
    stepper.runToNewPosition(0);
    stepper.runToNewPosition(2800);
    stepper.runToNewPosition(0);
    //stepper.runToNewPosition(120);
 digitalWrite(X_ENABLE_PIN, HIGH);
  
  //stepper.runSpeedToPosition();
  //stepper.run();
}

int getRotarylength(int unit){
 
  boolean runrotaryL = true;
  do   // loop while waiting for user to select.
  {
    switch(readEncoder()) 
    {  // analyze encoder response. Default is 0.


    case 1:  // ENCODER ROTATED UP. EQUIVALENT OF 'UP' BUTTON PUSHED
      if (length <1) break;
      Serial.println("+");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      //  if cursor is at top and menu is NOT at top
      //  move menu up one.
      length=length-unit;
      lcd.setCursor(22,2);
      Serial.print(length);
      lcd.print("mm:       ");
      lcd.setCursor(22,2);
      lcd.print("mm: " + String(length));     
      break;

    case 2:    // ENCODER ROTATED UP. EQUIVALENT OF 'DOWN' BUTTON PUSHED
    if (length > 9999) break;
      Serial.println("-");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      // this sees if there are menu items below the bottom of the LCD screen & sees if cursor is at bottom of LCD 
      length=length+unit;
      lcd.setCursor(22,2);
      Serial.print(length);
      lcd.print("mm:       ");
      lcd.setCursor(22,2);
      lcd.print("mm: " + String(length));      
      break;
    case 4:  // ENCODER BUTTON PUSHED FOR SHORT PERIOD & RELEASED.
      // EQUIVALENT TO 'SELECT' OR 'OKAY' BEING PUSHED 
      Serial.println("end sub menu");  
      lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
         lcd.print(" ");
      runrotaryL = false;
      break;      
}
  }while (runrotaryL == true);  //
}

int getRotarypcs(){
  boolean runrotaryPCS = true;
  do   // loop while waiting for user to select.
  {
    switch(readEncoder()) 
    {  // analyze encoder response. Default is 0.


    case 1:  // ENCODER ROTATED UP. EQUIVALENT OF 'UP' BUTTON PUSHED
      if (pcs <1) break;
      Serial.println("-- pcd");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      //  if cursor is at top and menu is NOT at top
      //  move menu up one.
      pcs--;
      lcd.setCursor(32,2);
      lcd.print(String(pcs) + "pcs.");     
      break;

    case 2:    // ENCODER ROTATED UP. EQUIVALENT OF 'DOWN' BUTTON PUSHED
      if (pcs > 99) break;
      Serial.println("++ pcs");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      // this sees if there are menu items below the bottom of the LCD screen & sees if cursor is at bottom of LCD 
      pcs++;
      lcd.setCursor(32,2);
      lcd.print(String(pcs) + "pcs.");      
      break;
    case 4:  // ENCODER BUTTON PUSHED FOR SHORT PERIOD & RELEASED.
      // EQUIVALENT TO 'SELECT' OR 'OKAY' BEING PUSHED 
      Serial.println("end sub menu");  
      runrotaryPCS = false;
      lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
         lcd.print(" ");
      break;      
}
  }while (runrotaryPCS == true);  //
}


int getRotaryMove(){
      digitalWrite(Y_ENABLE_PIN, LOW);
     // wait a few microseconds for the enable to take effect
     // (That isn't in the spec sheet I just added it for sanity.)
     delayMicroseconds(2);  
  boolean runrotaryM = true;
  do   // loop while waiting for user to select.
  {
    switch(readEncoder()) 
    {  // analyze encoder response. Default is 0.


    case 1:  // ENCODER ROTATED UP. EQUIVALENT OF 'UP' BUTTON PUSHED
      Serial.println("+");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      //  if cursor is at top and menu is NOT at top
      //  move menu up one.
      stepperForward.runToNewPosition(100);
      stepperForward.setCurrentPosition(0);
      Serial.print("Move +");
      break;

    case 2:    // ENCODER ROTATED UP. EQUIVALENT OF 'DOWN' BUTTON PUSHED
      Serial.println("-");
      timeoutTime = millis()+menuTimeout;  // reset timeout timer
      // this sees if there are menu items below the bottom of the LCD screen & sees if cursor is at bottom of LCD 
      stepperForward.runToNewPosition(-100);
      stepperForward.setCurrentPosition(0);
      Serial.print("Move -");     
      break;
    case 4:  // ENCODER BUTTON PUSHED FOR SHORT PERIOD & RELEASED.
      // EQUIVALENT TO 'SELECT' OR 'OKAY' BEING PUSHED 
      Serial.println("end sub menu");  
      lcd.setCursor(20,1);      // go to LCD line where new cursor should be & display it.
         lcd.print(" ");
         digitalWrite(Y_ENABLE_PIN, HIGH);
      runrotaryM = false;
      break;      
}
  }while (runrotaryM == true);  //
}


// returns 1 for right, -1 for left, or 0 for no movement
int readEncoder() {
  //Serial.print("read encoder ");
  moved = true;

  switch(encoder.tick()) {
  case '>': 
    return 1;
  case '<': 
    return 2;
  }
  if (digitalRead(BTN_ENC) == LOW) {
    delay(100);
    if (digitalRead(BTN_ENC) == LOW) {
    Serial.print("push ");
    return 4;
    }
  }

  moved = false;
  return 0;
}


static void beep()
{
    tone(BEEPER, 131,100);
    //tone(BEEPER, 165,100);
}

