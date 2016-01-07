/* Arduino USB HID Chorded Keyboard 
 * copied from everywhere
 */

int firstButton = 2;
int secondButton = 3;
int thirdButton = 4;
int fourthButton = 5;
int fifthButton = 6;

int first_state_initial = 0;
int second_state_initial = 0;
int third_state_initial = 0;
int fourth_state_initial = 0;
int fifth_state_initial = 0;

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
    int chord_char_final = 0;

    first_state_initial = digitalRead(firstButton);
    second_state_initial = digitalRead(secondButton);
    third_state_initial = digitalRead(thirdButton);
    fourth_state_initial = digitalRead(fourthButton);
    fifth_state_initial = digitalRead(fifthButton);
    
    if (first_state_initial == LOW) 
        chord_char = chord_char + 1; 

    if (second_state_initial == LOW)
        chord_char = chord_char + 2;

    if (third_state_initial == LOW)
        chord_char = chord_char + 4;

    if (fourth_state_initial == LOW)
        chord_char = chord_char + 8;

    if (fifth_state_initial == LOW)
        chord_char = chord_char + 16;
    
    //it looks like characters start at 4 on USB  
    if (chord_char != 0) {
        delay(50);
        int first_state_check = digitalRead(firstButton);
        int second_state_check = digitalRead(secondButton);
        int third_state_check = digitalRead(thirdButton);
        int fourth_state_check = digitalRead(fourthButton);
        int fifth_state_check = digitalRead(fifthButton);  
        if (first_state_check == first_state_initial &&
            second_state_check == second_state_initial &&
            third_state_check == third_state_initial &&
            fourth_state_check == fourth_state_initial &&
            fifth_state_check == fifth_state_initial) 
            {            
            if (chord_char == 27) {
                //this is for space
                chord_char_final = 44;
            } else if (chord_char == 28) {
                //this is for backspace
                chord_char_final = 42;
            } else if (chord_char == 29) {
                //this is for return
                chord_char_final = 40;
            } else {
                chord_char_final = chord_char + 3;
            }
            buf[2] = chord_char_final;
            //buf[2] = chord_char + 3;
            Serial.write(buf, 8); // Send keypress
            releaseKey();
            delay(250);
        }
    }     
}

void releaseKey() 
{
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8); // Release key  
}
