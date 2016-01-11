/* Arduino USB HID Chorded Keyboard 
 * copied from everywhere
 */

#include <Keyboard.h>

int first_button = 2;
int second_button = 3;
int third_button = 4;
int fourth_button = 5;
int fifth_button = 6;

int mode_upper_btn = 7;
int mode_number_btn = 8;

int mode_upper_led = 9;
int mode_number_led = 10;

int first_state_initial = 0;
int second_state_initial = 0;
int third_state_initial = 0;
int fourth_state_initial = 0;
int fifth_state_initial = 0;

int prev_chord_char = 0;

//character definitions from
//http://www.asciitable.com/
//in dec form and from
//https://www.arduino.cc/en/Reference/KeyboardWrite
int case_lower[] = { 0,
    97, //a
    98,
    99,
    100,
    101,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    109,
    110,
    111,
    112,
    113,
    114,
    115,
    116,
    117,
    118,
    119,
    120,
    121,
    122, //z
    32,  //space
    178, //backspace
    176, //return
    177, //escape
    46   //period
};

int case_upper[] = { 0,
    65, //A
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,  //Z
    32,  //space
    178, //backspace
    39,  //'
    34,  //"
    44   //,
};

int case_number[] = { 0,
    49, //1
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57, //9
    48, //0
    33, //!
    64, //@
    35, //#
    36, //$
    37, //%
    94, //^
    40, //(
    41, //)
    43, //+
    45, //-
    91, //[
    93, //]
    95, //_
    126,//~
    123,//{
    125,//}
    47, ///
    63, //?
    60, //<
    62, //>
    124 //|
};

int current_bank = 0;

void setup() 
{
    pinMode(first_button, INPUT_PULLUP);
    pinMode(second_button, INPUT_PULLUP);
    pinMode(third_button, INPUT_PULLUP);
    pinMode(fourth_button, INPUT_PULLUP);
    pinMode(fifth_button, INPUT_PULLUP);
    pinMode(mode_upper_btn, INPUT_PULLUP);
    pinMode(mode_number_btn, INPUT_PULLUP);
    pinMode(mode_upper_led, OUTPUT);
    pinMode(mode_number_led, OUTPUT);

    digitalWrite(mode_upper_led, LOW);
    digitalWrite(mode_number_led, LOW);

    Keyboard.begin();
  
    delay(200);

}

void loop() 
{
    int chord_char = 0;
    int chord_char_final = 0;

    if (digitalRead(mode_upper_btn) == LOW) {
        switch (current_bank) {
        case 1:
            current_bank = 0;
            digitalWrite(mode_upper_led, LOW);
            delay(150);
            break;
        default:
            current_bank = 1;
            digitalWrite(mode_upper_led, HIGH);
            digitalWrite(mode_number_led, LOW);
            delay(150);
            break;
        }
    }

    if (digitalRead(mode_number_btn) == LOW) {
        switch (current_bank) {
        case 2:
            current_bank = 0;
            digitalWrite(mode_number_led, LOW);
            delay(150);
            break;
        default:
            current_bank = 2;
            digitalWrite(mode_number_led, HIGH);
            digitalWrite(mode_upper_led, LOW);
            delay(150);
            break;
        }
    }

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
            chord_char_final = chord_char;
            if (chord_char_final == prev_chord_char) {
                prev_chord_char = 0;  
            } else {
                switch (current_bank) {
                case 0:
                    Keyboard.write(case_lower[chord_char_final]);
                    break;
                case 1:
                    Keyboard.write(case_upper[chord_char_final]);
                    break;
                case 2:
                    Keyboard.write(case_number[chord_char_final]);
                    break;
                }
                delay(50);
                prev_chord_char = chord_char_final;
            }
        }
    }     
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
