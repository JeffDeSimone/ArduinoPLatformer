#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int *holeArr; 
int pointerCount = 0;
int x = 1;
int y = 50;
int sectionCounter = 0;

 //CODE FOR JOYSTICK
 int ledPin = 13;
 const int clickPin = 2;
 const int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
 int joyVal;       
 int joyLast;
 int joyClick = 0;
 int holeArr1 [2]= {17,18}; 


 void setup() {          // initializes digital pins 0 to 7 as outputs
            // variable to read the value from the analog pin 1

  pinMode(clickPin, INPUT_PULLUP);           // set pin to input 
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 55);
  // Display static text
  display.println("------------------------------------------------------------");
  display.display();

}

void loop() {
  
  
  joyStickHandler();
  if(digitalRead(clickPin)==0){
    jumpButton();
  }
  if(sectionCounter > 0){
    checkHole();
  }

}

void moveSprite(int x, int y){

  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.print("0");
  display.display();

}

void clearSprite(int x, int y){
    display.setTextColor(BLACK);
    display.setCursor(x, y);
    display.print("0");
}

void joyStickHandler(){
   
    joyVal = analogRead(joyPin1);
    if(x <= 100 && x >= 1 ){
    clearSprite(x,y);
    if(joyVal>600){
      x++;
    }
    delay(1);
    if(joyVal<500){
      x--;
    }
    moveSprite(x,y);
  }
  if(x>100){
    sectionCounter++;
    newSection();
  }
}

void jumpButton(){
  for( int a= 0; a < 5; a = a + 1 ) {
    y=y-a;
    moveSprite(x, y);
    joyStickHandler(); 
    joyStickHandler(); 
    clearSprite(x, y);
    
    
    
  }
  for( int a= 0; a < 5; a = a + 1 ) {
    y=y+a;
    moveSprite(x, y);
    joyStickHandler(); 
    joyStickHandler(); 
    clearSprite(x, y);
    
    
  }
}


void checkHole(){
  
  for(int i = 0; i < pointerCount; i++) {
    int val = holeArr[i];
    //Serial.println(x);
    Serial.println(val);
    if(x == val && y==50){
      Serial.println("ded");     
      
    }
}
}

void newSection(){

  //create array for holes
  

  display.setTextColor(WHITE);
  display.setCursor(0, 55);
  // Display static text
  display.clearDisplay();
  
  if(sectionCounter == 1){
    
    holeArr = holeArr1;
    pointerCount = 2;
    display.println("--- --------------");
    display.display();
  }
  if(sectionCounter == 2){
    int holeArr2 [1] = {1}; 
    display.println("------- --- ------");
    display.display();
  }
  if(sectionCounter == 3){
    display.println("-------  ---------");
    display.display();
  }
  else{
    display.println("------------------");
    display.display();
  }
  x=1;
}
