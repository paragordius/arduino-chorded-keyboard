/* Arduino USB HID Chorded Keyboard 
 * copied from everywhere
 */

int first_button = 2;
int second_button = 3;
int third_button = 4;
int fourth_button = 5;
int fifth_button = 6;

int first_state_initial = 0;
int second_state_initial = 0;
int third_state_initial = 0;
int fourth_state_initial = 0;
int fifth_state_initial = 0;

int prev_chord_char = 0;

uint8_t buf[8] = { 
    0 };   /* Keyboard report buffer */

void setup() 
{
    pinMode(first_button, INPUT_PULLUP);
    pinMode(second_button, INPUT_PULLUP);
    pinMode(third_button, INPUT_PULLUP);
    pinMode(fourth_button, INPUT_PULLUP);
    pinMode(fifth_button, INPUT_PULLUP);
  
    Serial.begin(9600);
  
    delay(200);
}

void loop() 
{
    int chord_char = 0;
    int chord_char_final = 0;

    first_state_initial = digitalRead(first_button);
    second_state_initial = digitalRead(second_button);
    third_state_initial = digitalRead(third_button);
    fourth_state_initial = digitalRead(fourth_button);
    fifth_state_initial = digitalRead(fifth_button);
    
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
    
    if (chord_char != 0) {
        delay(50);
        if (state_change() == 0) {
            switch (chord_char) {
            case 27:
                //this is for space
                chord_char_final = 44;
                break;
            case 28:
                //this is for backspace
                chord_char_final = 42;
                break;
            case 29:
                //this is for return
                chord_char_final = 40;
                break;
            case 30:
                //this is for escape
                chord_char_final = 41;
                break;
            case 31:
                //this is for period
                chord_char_final = 99;
                break;
            default:
                chord_char_final = chord_char + 3;
                break;
            }
            buf[2] = chord_char_final;
            if (chord_char_final == prev_chord_char) {
                //delay(250);
                prev_chord_char = 0;  
            } else {
                Serial.write(buf, 8); // Send keypress
                release_key();
                delay(50);
                prev_chord_char = chord_char_final;
            }
        }
    }     
}

void release_key() 
{
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8); // Release key  
}

//the point of this block is to wait to see
//if additional buttons get pressed before
//writing the final output
int state_change()
{
    int first_state_check = digitalRead(first_button);
    int second_state_check = digitalRead(second_button);
    int third_state_check = digitalRead(third_button);
    int fourth_state_check = digitalRead(fourth_button);
    int fifth_state_check = digitalRead(fifth_button);  
    if (first_state_check == first_state_initial &&
	second_state_check == second_state_initial &&
	third_state_check == third_state_initial &&
	fourth_state_check == fourth_state_initial &&
	fifth_state_check == fifth_state_initial) 
        return 0;
    else 
        return 1;
}

int keys_held()
{
    if (digitalRead(first_button) == HIGH &&
    digitalRead(second_button) == HIGH &&
    digitalRead(third_button) == HIGH &&
    digitalRead(fourth_button) == HIGH &&
    digitalRead(fifth_button) == HIGH)
        return 0;
    else
        return 1;
}
