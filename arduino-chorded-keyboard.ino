/* Arduino USB HID Chorded Keyboard 
 * copied from everywhere
 */

int firstButton = 2;
int secondButton = 3;
int thirdButton = 4;
int fourthButton = 5;
int fifthButton = 6;

int firstState = 0;
int secondState = 0;
int thirdState = 0;
int fourthState = 0;
int fifthState = 0;

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */

void setup() 
{
  pinMode(firstButton, INPUT_PULLUP);
  pinMode(secondButton, INPUT_PULLUP);
  pinMode(thirdButton, INPUT_PULLUP);
  pinMode(fourthButton, INPUT_PULLUP);
  pinMode(fifthButton, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  delay(200);
}

void loop() 
{
  int chord_char = 0;
  
  firstState = digitalRead(firstButton);
  secondState = digitalRead(secondButton);
  thirdState = digitalRead(thirdButton);
  fourthState = digitalRead(fourthButton);
  fifthState = digitalRead(fifthButton);
    
  if (firstState == LOW)
      chord_char = chord_char + 1; 

  if (secondState == LOW)
      chord_char = chord_char + 2;

  if (thirdState == LOW)
      chord_char = chord_char + 4;

  if (fourthState == LOW)
      chord_char = chord_char + 8;

  if (fifthState == LOW)
      chord_char = chord_char + 16;
    
  //it looks like characters start at 4 on USB
  //chord_char = 4;
  if (chord_char != 0) {
      buf[2] = chord_char + 3;
      Serial.write(buf, 8); // Send keypress
      releaseKey();  //long randomDelay = random(1000, 10000);
  }    
  delay(200);
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}
