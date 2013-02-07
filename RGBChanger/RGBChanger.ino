/*     ---------------------------------------------------------
 *     |  Experimentation Kit for Arduino Example Code         |
 *     |  CIRC-RGB .: Colourful Light :. (RGB LED)             |
 *     ---------------------------------------------------------
 * 
 * We've blinked an LED and controlled eight in sequence now it's time to 
 * control colour. Using an RGB LED (actual 3 LEDs in a single housing)  
 * we can generate any colour our heart desires.
 *
 * (we'll also use a few programming shortcuts to make the code 
 * more portable/readable)
 */


//RGB LED pins
int ledDigitalOne[] = {9, 10, 11}; //the three digital pins of the digital LED 
                                   //9 = redPin, 10 = greenPin, 11 = bluePin

const boolean ON = LOW;     //Define on as LOW (this is because we use a common 
                            //Anode RGB LED (common pin is connected to +5 volts)
const boolean OFF = HIGH;   //Define off as HIGH

//Predefined Colors
const boolean RED[] = {ON, OFF, OFF};    
const boolean GREEN[] = {OFF, ON, OFF}; 
const boolean BLUE[] = {OFF, OFF, ON}; 
const boolean YELLOW[] = {ON, ON, OFF}; 
const boolean CYAN[] = {OFF, ON, ON}; 
const boolean MAGENTA[] = {ON, OFF, ON}; 
const boolean WHITE[] = {ON, ON, ON}; 
const boolean BLACK[] = {OFF, OFF, OFF}; 
char inData[20];
char inChar=-1;
byte index = 0;
//An Array that stores the predefined colors (allows us to later randomly display a color)
const boolean* COLORS[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK};

void setup(){
  for(int i = 0; i < 3; i++){
   pinMode(ledDigitalOne[i], OUTPUT);   //Set the three LED pins as outputs
  }
  Serial.begin(9600); //Set up serial
  Serial.println("Please enter a color"); //Print to console asking for a color
}
char Comp(const char* This) {
    while (Serial.available() > 0) // Don't read unless
                                   // there you know there is data
    {
        if(index < 19) // One less than the size of the array
        {
            inChar = Serial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }

    if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        return(0);
    }
    else {
        return(1);
    }
}
void loop(){


  if(Comp("red")==0){ //checks if sent red
   setColor(ledDigitalOne, RED);
  }
  else if(Comp("blue")==0){//checks if sent blue
   setColor(ledDigitalOne, BLUE);
  }
  else if(Comp("green")==0){//checks if sent green
   setColor(ledDigitalOne, GREEN);
  }
   if(Comp("yellow")==0){//checks if sent yellow
   setColor(ledDigitalOne, YELLOW);
  }
  else if(Comp("cyan")==0){//checks if sent cyan
   setColor(ledDigitalOne, CYAN);
  }
  else if(Comp("magenta")==0){//checks if sent magenta
   setColor(ledDigitalOne, MAGENTA);
  }
   if(Comp("black")==0){//checks if sent black
   setColor(ledDigitalOne, BLACK);
  }
  else if(Comp("white")==0){//checks if sent white
   setColor(ledDigitalOne, WHITE);
  }
  

}


/* Sets an led to any color
   led - a three element array defining the three color pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin)
   color - a three element boolean array (color[0] = red value (LOW = on, HIGH = off), color[1] = green value, color[2] =blue value)
*/
void setColor(int* led, boolean* color){
 for(int i = 0; i < 3; i++){
   digitalWrite(led[i], color[i]);
 }
}

/* A version of setColor that allows for using const boolean colors
*/
void setColor(int* led, const boolean* color){
  boolean tempColor[] = {color[0], color[1], color[2]};
  setColor(led, tempColor);
}
