// Include Libraries
#include "Arduino.h"
#include "Potentiometer.h"
#include "Button.h"
#include <Keyboard.h>


// Pin Definitions
#define POTENTIOMETER_PIN_SIG	A0
#define PUSHBUTTON_PIN_2	8



// Global variables and defines

// object initialization
Potentiometer potentiometer(POTENTIOMETER_PIN_SIG);
Button pushButton(PUSHBUTTON_PIN_2);



// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
const int THRESHOLD = 3;
char menuOption = 0;
long time0;
int volume = 0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    pushButton.init();

    Keyboard.begin();
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    // handle volume
    int potentiometerVal = potentiometer.read();
    //Serial.print(F("Val: ")); Serial.println(potentiometerVal);
    if (potentiometerVal == 0) {
        Serial.println("volume reset");
        pressCtrlWithKey(KEY_F8);
    } else if (potentiometerVal == 1023) {
        Serial.println("volume max");
        pressCtrlWithKey(KEY_F2);
    } else if (potentiometerVal > volume + THRESHOLD) {
        pressCtrlWithKey(KEY_F7);
        Serial.println("high");
    } else if (potentiometerVal < volume - THRESHOLD) {
        pressCtrlWithKey(KEY_F6);
        Serial.println("low");
    }
    volume = potentiometerVal;

    // check buttons
    bool pushButtonVal = pushButton.read();
    if (pushButtonVal) {
        Serial.print(F("push button: ")); Serial.println(pushButtonVal);
        Keyboard.press(' ');
    }
    
    delay(400);
    /*
    if(menuOption == '1') {
    // Potentiometer - Test Code
    int potentiometerVal = potentiometer.read();
    Serial.print(F("Val: ")); Serial.println(potentiometerVal);

    }
    else if(menuOption == '2') {
    // PushButton - Test Code
    //Read pushbutton state. 
    //if button is not pushed function will return LOW (0). if it is pushed function will return HIGH (1).
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    //try also pushButton.onPress(), .onRelease() and .onChange() for debounce.
    bool pushButtonVal = pushButton.read();
    Serial.print(F("Val: ")); Serial.println(pushButtonVal);

    }
    
    
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    */
}


void pressCtrlWithKey(int key)  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(key);
    delay(100);
    Keyboard.releaseAll();
}

// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Potentiometer"));
    Serial.println(F("(2) PushButton"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {
            if(c == '1') 
    			Serial.println(F("Now Testing Potentiometer"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing PushButton"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
            }
        }
    }

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
