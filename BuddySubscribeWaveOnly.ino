// ---------------------------------
// Task 3.3D Particle - Buddy system
// ---------------------------------

/*-------------
Every program based on Wiring (programming language used by Arduino, 
and Particle devices) has two essential parts:
setup - runs once at the beginning of your program
loop - runs continuously over and over

This program will see a Particle device (in this case an Argon) subscribe to an event 
being published by another Particle device (in this case a Photon).

This program is for the subscribing by the Particle Argon to an event published by the 
Particle Photon.
-------------*/

// This task will have many variables, some will be constant such as the pins, number of 
// blinks and time of each blink.

const pin_t WAVE_LED = D6; // Instead of writing D6 over and over again, we'll write WAVE_LED
// You'll need to wire a blue LED to this pin.
const int WAVE_BLINKS = 3; // The blue led will blink 3 times
const int WAVE_TIME = 1000; // Each blink will last 1000 milliseconds

const char *RECIEVED_EVENT = "Deakin_RIOT_SIT210_Photon_Buddy"; 
const char *RESPONSE_EVENT = "Deakin_RIOT_SIT210_Argon_Buddy"; 
// Event's name will be similar to what it would of been previously before Particle stopped 
// allowing public events to be published in August 2020.

// Having declared these variables, declaring functions.
void subscriptionHandler(const char *event, const char *data);
void blinkLED(int pin, int blinks, int blinkTime);

// The following line is optional, but recommended in most firmware. It allows your code to 
// run before the cloud is connected. In this case, it will begin blinking almost immediately 
// instead of waiting until breathing cyan,
SYSTEM_THREAD(ENABLED);

// Now let's move on to the setup function.
// The setup function is a standard part of any microcontroller program.
// It runs only once when the device boots up or is reset.

void setup() {
    // We are going to tell our device that D6 (which we named WAVE_PIN) is going to be output
	// (That means that we will be sending voltage to them)

	pinMode(WAVE_LED, OUTPUT);
	
    Particle.subscribe(RECIEVED_EVENT, subscriptionHandler);
}

// Next we have the loop function, the other essential part of a microcontroller program.
// This is blank as its dealt with by subscription handler function.
void loop() {
    //Left blank
}

// Function to subscribe to wave event being published by Photon. Will publish a string on the Particle 
// console.
void subscriptionHandler(const char *event, const char *data) {
    if (strcmp(data, "wave") == 0) {
        blinkLED(WAVE_LED, WAVE_BLINKS, WAVE_TIME);
    } 
    String message = String::format("Completed: %s event", data);
    Particle.publish(RESPONSE_EVENT, message);
}

// Function to blink blue LED the amount of times and length mentioned at start of code.
void blinkLED(int pin, int blinks, int blinkTime) {
    for(int i = 0; i < blinks; i++) {
        digitalWrite(WAVE_LED, HIGH);
        delay(WAVE_TIME);
        digitalWrite(WAVE_LED, LOW);
        delay(WAVE_TIME);
    }
}
