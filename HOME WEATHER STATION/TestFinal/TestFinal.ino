#include <LiquidCrystal.h>
#include <DHT.h>

//Constants
#define DHT11_PIN 2
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);
//LCD pin to Arduino
int redpin = 11;
int bluepin = 13;
int greenpin = 12;
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
float hum;  //Stores humidity value
float tempc; //Stores temperature value
float tempf; //Stores temperature value
float tempK; //Stores temperature value
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

// section of the operateMainMenu() function below. You will also have to add additional void functions (i.e. menuItem11, menuItem12, etc.) to the program.

String menuItems[] = {"Celsius", "Fahrenheit", "Kelvin", "Humidity Chk", "Temp Chk"};

// Navigation button variables
int readKey;
int savedDistance = 0;

// Menu control variables
int menuPage = 0;
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int cursorPosition = 0;

// Creates 3 custom characters for the menu display
byte downArrow[8] = {
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};

byte upArrow[8] = {
  0b00100, //   *
  0b01110, //  ***
  0b10101, // * * *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100  //   *
};

byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

#include <Wire.h>
#include <LiquidCrystal.h>



void setup() {

  // Initializes serial communication
  Serial.begin(9600);
  dht.begin();
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  
  // Initializes and clears the LCD screen
  lcd.begin(16, 2);
  lcd.clear();

  // Creates the byte for the 3 custom characters
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);

/*pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(3,OUTPUT);*/
  lcd.setCursor(4,0);
  lcd.print("Welcome");
  delay(2000);
  lcd.clear();
}

void loop() {
  mainMenuDraw();
  drawCursor();
  operateMainMenu();
}

// This function will generate the 2 menu items that can fit on the screen. They will change as you scroll through your menu. Up and down arrows will indicate your current menu position.
void mainMenuDraw() {
  Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}

// When called, this function will erase the current cursor and redraw it based on the cursorPosition and menuPage variables.
void drawCursor() {
  for (int x = 0; x < 2; x++) {     // Erases current cursor
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  // The menu is set up to be progressive (menuPage 0 = Item 1 & Item 2, menuPage 1 = Item 2 & Item 3, menuPage 2 = Item 3 & Item 4), so
  // in order to determine where the cursor should be you need to see if you are at an odd or even menu page and an odd or even cursor position.
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is even and the cursor position is even that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is even and the cursor position is odd that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is odd and the cursor position is even that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is odd and the cursor position is odd that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}


void operateMainMenu() {
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 0: // When button returns as 0 there is no action taken
        break;
      case 1:  // This case will execute if the "forward" button is pressed
        button = 0;
        switch (cursorPosition) { // The case that is selected here is dependent on which menu page you are on and where the cursor is.
          case 0:
            menuItem1();
            break;
          case 1:
            menuItem2();
            break;
          case 2:
            menuItem3();
            break;
          case 3:
            menuItem4();
            break;
          case 4:
            menuItem5();
            break;
          
        }
        activeButton = 1;
        mainMenuDraw();
        drawCursor();
        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        }
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
    }
  }
}

// This function is called whenever a button press is evaluated. The LCD shield works by observing a voltage drop across the buttons all hooked up to A0.
int evaluateButton(int x) {
  int result = 0;
  if (x < 50) {
    result = 1; // right
  } else if (x < 195) {
    result = 2; // up
  } else if (x < 380) {
    result = 3; // down
  } else if (x < 790) {
    result = 4; // left
  }
  return result;
}

// If there are common usage instructions on more than 1 of your menu items you can call this function from the sub
// menus to make things a little more simplified. If you don't have common instructions or verbage on multiple menus
// I would just delete this void. You must also delete the drawInstructions()function calls from your sub menu functions.
void drawInstructions() {
  lcd.setCursor(0, 1); // Set cursor to the bottom line
  lcd.print("Use ");
  lcd.write(byte(1)); // Up arrow
  lcd.print("/");
  lcd.write(byte(2)); // Down arrow
  lcd.print(" buttons");
}

void menuItem1() { // Function executes when you select the Yellow item from main menu
  int activeButton = 0;

  lcd.clear();



  while (activeButton == 0) {


    //int chk = dht.read11(DHT11_PIN);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();//DHT.humidity;
    tempc= dht.readTemperature();//DHT.temperature;

    //Print temp and humidity values to serial monitor    
    
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    lcd.print("Humi:");
    lcd.setCursor(6,0);
    lcd.print(tempc); 
    lcd.print(" C");  
    lcd.setCursor(6,1);
    lcd.print(hum);
    lcd.print(" %");
    if(tempc<19){
    digitalWrite(bluepin, LOW);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, HIGH);  
  }
  else if(tempc>22){
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, LOW);
    digitalWrite(greenpin, HIGH);
  }
  else{
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, LOW);
  }

    
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(1000);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        digitalWrite(13,LOW);
        break;
    }
  }
}

void menuItem2() { // Function executes when you select the Green item from main menu
  int activeButton = 0;

  lcd.clear();

  //int chk = DHT.read11(DHT11_PIN);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();//DHT.humidity;
    tempc= dht.readTemperature();//DHT.temperature;
    tempf= (tempc*1.8)+32;
    //Print temp and humidity values to serial monitor    
    
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    lcd.print("Humi:");
    lcd.setCursor(6,0);
    lcd.print(tempf); 
    lcd.print(" F");  
    lcd.setCursor(6,1);
    lcd.print(hum);
    lcd.print(" %");
    if(tempc<19){
    digitalWrite(bluepin, LOW);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, HIGH);  
  }
  else if(tempc>22){
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, LOW);
    digitalWrite(greenpin, HIGH);
  }
  else{
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, LOW);
  }
    
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(1000);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        digitalWrite(12,LOW);
        break;
    }
  }
}

void menuItem3() { // Function executes when you select the Red item from main menu
  int activeButton = 0;

  lcd.clear();
 
  //int chk = DHT.read11(DHT11_PIN);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();//DHT.humidity;
    tempc= dht.readTemperature();//DHT.temperature;
    tempK= tempc+273;
    //Print temp and humidity values to serial monitor    
    
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    lcd.print("Humi:");
    lcd.setCursor(6,0);
    lcd.print(tempK); 
    lcd.print(" K");  
    lcd.setCursor(6,1);
    lcd.print(hum);
    lcd.print(" %");
    if(tempc<19){
    digitalWrite(bluepin, LOW);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, HIGH);  
  }
  else if(tempc>22){
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, LOW);
    digitalWrite(greenpin, HIGH);
  }
  else{
    digitalWrite(bluepin, HIGH);
    digitalWrite(redpin, HIGH);
    digitalWrite(greenpin, LOW);
  }

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(1000);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        digitalWrite(11,LOW);
        break;
    }
  }
}

void menuItem4() { // Function executes when you select the Purple item from main menu
  int activeButton = 0;
  
  //int chk = DHT.read11(DHT11_PIN);
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();//DHT.humidity;
  //  tempc= dht.readTemperature();//DHT.temperature;
  
  lcd.clear();
  HumidityCheck(hum);
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(1000);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        digitalWrite(3,LOW);
        break;
    }
  }
}
void menuItem5() { // Function executes when you select the Purple item from main menu
  int activeButton = 0;
  
  //int chk = DHT.read11(DHT11_PIN);
  //Read data and store it to variables hum and temp
  //hum = dht.readHumidity();//DHT.humidity;
  tempc= dht.readTemperature();//DHT.temperature;
  
  lcd.clear();
  TempCheck(tempc);
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(1000);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        digitalWrite(3,LOW);
        break;
    }
  }
}

void HumidityCheck(float humidity){
 
  if(humidity<30){
    lcd.setCursor(0,0);
    lcd.print("Dry Environment");
    }
  else if(humidity>=30&&humidity<=45){
    lcd.setCursor(0,0);
    lcd.print("Perfect Environment");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Moist Environment");
  }
  }



void TempCheck(float temperature) {
if(temperature<19){
    lcd.setCursor(0,0);
    lcd.print("Cold Environment");
    }
  else if(temperature>=19&&temperature<=22){
    lcd.setCursor(0,0);
    lcd.print("Perfect Environment");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Hot Environment");
  }
  }
