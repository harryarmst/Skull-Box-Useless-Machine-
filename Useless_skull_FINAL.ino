/* 
For mini blue servos: Red +5V, Brown Ground, Orange signal
For DS servos: Red +5V, Black Ground, White signal

Item      Arduino Pin     RJ45 color      Skull end Jumper color     
Jaw           2           White/Orange          Blue                  Note: white/Blue is +5V, Blue is ground   
Right Eye     3             Orange            Orange      
Left Eye      4             Brown             Brown     
Eyebrows      5             Green             Green     
Up            24         was 6
Down          25         was 7
Head turn     8             orange      jumper from thin cat6        
Hand          27 was 9 but hung up the program             jumps directly to hand cable white.       
MP3           10            not used anymore        
switch        26        was 11                   
Head Door     28
hand door     29
Demo switch   30
Mumble on off 31
Power LED     32          

Teensy uses pins 6,7,9,10,11,12,13,14,15,18,19,20,23

*/

//Teensy audio shield:
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playSdWav1;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

// End Teensy audio shield

int stepval = 0; // Keep track of what step we are on
int idledelay = 15000; //idle delay bfore stepval = 0 again
unsigned long time_now = 0;
int mdelay = 30000;
unsigned long m1_now = 0;
unsigned long m2_now = 0;
int mum = 1;


#include <Servo.h>
const int up = 24; // head up relay pin
const int down = 25; // head down relay pin

Servo jaw;  // create servo object to control a servo
Servo reye; 
Servo leye;
Servo brow;
Servo head;
Servo hand;
Servo headdoor;
Servo handdoor;
// twelve servo objects can be created on most boards


const int redswitch = 26;
const int demo = 30;
const int mumswitch = 31;
// int upval = 0;
// int downval = 0;
  
void setup() {
  Serial.begin(9600);

  jaw.attach(2);  // attaches the servo on pin 2 to the servo object
reye.attach(3);
leye.attach(4);
brow.attach(5);
head.attach(8);
hand.attach(27);
headdoor.attach(28);
handdoor.attach(29);
  //door.attach(12);
  // 26 is redswitch
 
// turn head relays off
pinMode(up, OUTPUT);
pinMode(down, OUTPUT);
digitalWrite(up, HIGH);
digitalWrite(down, HIGH);

pinMode(redswitch, INPUT_PULLUP);
pinMode(mumswitch, INPUT_PULLUP);
pinMode(demo, INPUT_PULLUP);
pinMode(32, OUTPUT);

head.write(90);
hand.write(76); // hand retracted
jaw.write(0);  // jaw closed
reye.write(40); //center
leye.write(40);
brow.write(0);
headdoor.write(5);
handdoor.write (0);
digitalWrite (32,HIGH);

//More Audio setup:
AudioMemory(8);
sgtl5000_1.enable();
sgtl5000_1.volume(0.8);
SPI.setMOSI(SDCARD_MOSI_PIN);
SPI.setSCK(SDCARD_SCK_PIN);
if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  Serial.println("end of setup");
  playSdWav1.play("m2.WAV");
}



void loop() {
int button = digitalRead(redswitch);
  // Serial.print("button is: ");
  //  Serial.print(button);
  //  Serial.print("  stepval is ");
  //  Serial.println(stepval);
int demomode = digitalRead(demo);
int mumswitchstate = digitalRead(mumswitch); 

// TIME OUT RESET START
if (millis() > (time_now + idledelay)){stepval = 0;}
// TIME OUT RESET END

//Mumble sounds begin
Serial.println("outside");
  Serial.println(mumswitchstate);
mumswitchstate = digitalRead(mumswitch);
if (mumswitchstate = HIGH){
digitalWrite(32, LOW);}
else {digitalWrite(32,HIGH);
  /*
  mumswitchstate = digitalRead(mumswitch);
 Serial.println("inside");
  Serial.println(mumswitchstate);
if (mum==1){
if (millis() > (m1_now+mdelay)){
playSdWav1.play("m1.WAV");
 m1_now=millis();
 m2_now=millis();
 mum=2;
 mumswitchstate = digitalRead(mumswitch);
 }
}
if (mum==2){
  mumswitchstate = digitalRead(mumswitch);
if (millis() > (m2_now+mdelay)){
 playSdWav1.play("m2.WAV");
  m2_now=millis();
  m1_now=millis();
  mum=1;
  mumswitchstate = digitalRead(mumswitch);
}
}
*/
}
mumswitchstate = digitalRead(mumswitch);
// Demo mode DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
if (demomode == LOW){
  // Raise head
headdoor.write(85);
digitalWrite(up, LOW);
delay(2000);
digitalWrite(up, HIGH);
head.write(180);
// Raise head end
// Move jaw for who keeps doing that. Jaw.write (60) is fully open, (0) is closed
delay(1000);
 jaw.write(0);
 delay(1000);
 jaw.write(60);
 delay(1000);
 jaw.write(0);
delay(1000);
 jaw.write(60);
 delay(1000);
 jaw.write(0); // Jaw closed
 delay(1000);
 jaw.write(60);
 delay(1000);
 jaw.write(0);
 delay(1000);
 jaw.write(60);
 delay(1000);
 jaw.write(0);
 // END jaw move
 //move eyes
 reye.write(10);
 leye.write(10);
 delay(1000);
 reye.write(70);
 leye.write(70);
 delay(1000);
  reye.write(10);
 leye.write(10);
 delay(1000);
 reye.write(70);
 leye.write(70);
 delay(1000);
 reye.write(40); //back to center
 leye.write(40);
 brow.write(70);
 delay(500);
 brow.write(0);
 delay(500);
 brow.write(70);
 delay(500);
 brow.write(0);
 delay(500);
 //center head
 head.write(90);
 
// Lower head
digitalWrite(down, LOW);
delay(1500);
digitalWrite(down, HIGH);
headdoor.write(5);
// Lower head end

demomode = digitalRead(demo);
time_now=millis();
m2_now=millis();
m1_now=millis();
}
// demo mode done DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDd
// Step One 1111111111111111111111111111111111111111111111111111111111111111
 if ((button == LOW) && (stepval == 0)){
//  Serial.println("step 1");
playSdWav1.play("1.WAV");
stepval=1;
delay(4500); 
//Shut the switch off begin
handdoor.write(80);
hand.write(30);
delay(1000);
hand.write(76);
delay(200);
handdoor.write(0);
//Shut the switch off end
button = digitalRead(redswitch);
time_now=millis();
m2_now=millis();
m1_now=millis();
}
// End step One 111111111111111111111111111111111111111111111111111111111111

// Step Two 2222222222222222222222222222222222222222222222222222222222222222
 if ((button == LOW) && (stepval == 1)){
playSdWav1.play("2.WAV");
stepval=2;
delay(3000);
//Shut the switch off begin
handdoor.write(80);
hand.write(30);
delay(1000);
hand.write(76);
delay(200);
handdoor.write(0);
button = digitalRead(redswitch);
time_now=millis();
m2_now=millis();
m1_now=millis();
 }
 // End step Two 222222222222222222222222222222222222222222222222222222222222

 // Step Three 33333333333333333333333333333333333333333333333333333333333333
 if ((button == LOW) && (stepval == 2)){
  stepval=3;
// Raise head
headdoor.write(85);
digitalWrite(up, LOW);
delay(2000);
digitalWrite(up, HIGH);
// Raise head end
playSdWav1.play("3.WAV");
// Move jaw for who keeps doing that. Jaw.write (60) is fully open, (0) is closed
delay(500);
 jaw.write(0);
 delay(300);
 jaw.write(30);
 delay(200);
 jaw.write(0);
delay(100);
 jaw.write(30);
 delay(200);
 jaw.write(0); // Jaw closed
 delay(200);
 jaw.write(30);
 delay(200);
 jaw.write(0);
 delay(200);
 jaw.write(30);
 delay(200);
 jaw.write(0);
 // END jaw move
 //Turn head
 head.write(140);
 delay(1500);
 // Say "you?"
 jaw.write(40);
 delay(500);
 jaw.write(0);
 delay(500);
  //Shut the switch off begin
handdoor.write(80);
hand.write(30);
delay(1000);
hand.write(76);
delay(200);
handdoor.write(0);
//delay(500);
head.write(90);
// shut the switch off end

// Lower head
digitalWrite(down, LOW);
delay(1500);
digitalWrite(down, HIGH);
headdoor.write(5);
// Lower head end

button = digitalRead(redswitch);
time_now=millis();
m2_now=millis();
m1_now=millis();
 }
// End Step Three 33333333333333333333333333333333333333333333333333333333333

 // Step Four 444444444444444444444444444444444444444444444444444444444444444
 if ((button == LOW) && (stepval == 3)){ //REMEMBER TO CHANGE THESE
 stepval=4;
// Raise head
headdoor.write(85);
digitalWrite(up, LOW);
delay(1500);
digitalWrite(up, HIGH);
// Raise head end
// Trigger sound #4
 playSdWav1.play("4a.WAV");
// End trigger sound #4
// Move jaw for Stop it....Im watching you. Jaw.write (60) is fully open, (0) is closed
 delay(600);
 jaw.write(60); //ahhhhh
 delay(800);
 jaw.write(0);
delay(700);
 jaw.write(30); //stop it
 delay(200);
 jaw.write(0); // Jaw closed
 delay(200);
 jaw.write(30);
 delay(100);
 jaw.write(0);
 // END jaw move
 //move eyes
 reye.write(10);
 leye.write(10);
 delay(800);
 reye.write(70);
 leye.write(70);
 delay(800);
  reye.write(10);
 leye.write(10);
 delay(800);
 reye.write(70);
 leye.write(70);
 delay(700);
 reye.write(40); //back to center
 leye.write(40);
 // Say "im watching you"
 delay(500);
 jaw.write(30);
 delay(250);
 jaw.write(0);
 delay(150);
 jaw.write(30);
 delay(250);
 jaw.write(0);
 delay(150);
 jaw.write(30);
 delay(250);
 jaw.write(0);
 delay(150);
 jaw.write(30);
 delay(250);
 jaw.write(0);
 delay(1000);
 //jaw move end 
 
// Lower head
digitalWrite(down, LOW);
delay(1500);
digitalWrite(down, HIGH);
headdoor.write(5);
// Lower head end

//Shut the switch off begin
handdoor.write(80);
hand.write(30);
delay(1000);
hand.write(76);
delay(200);
handdoor.write(0);
//Shut the switch off end
delay(500);
playSdWav1.play("4b.WAV");

button = digitalRead(redswitch);
time_now=millis();
m2_now=millis();
m1_now=millis();
 }

// End Step Four 444444444444444444444444444444444444444444444444444444444444444
 
// Step Five 555555555555555555555555555555555555555555555555555555555555555555
 if ((button == LOW) && (stepval == 4)){ //REMEMBER TO CHANGE THESE
 //stepval=0;
// Raise head
headdoor.write(85);
digitalWrite(up, LOW);
delay(1500);
digitalWrite(up, HIGH);
// Raise head end
// Trigger sound #5a meeh
 playSdWav1.play("5a.WAV");
// End trigger sound #5a
// Move jaw for Stop it....Im watching you. Jaw.write (60) is fully open, (0) is closed
 delay(100);
 head.write(140);
 jaw.write(60);
 reye.write(70);
 leye.write(10);
 brow.write(70);
 delay(1200);
 jaw.write(0);
 reye.write(40); //normal
 leye.write(40); //normal
brow.write(0);
 delay(800);
 
 head.write(90);
jaw.write(60);
 reye.write(70);
 leye.write(10);
 brow.write(70);
 delay(1200);
 jaw.write(0);
 reye.write(40); //normal
 leye.write(40); //normal
brow.write(0);
 delay(800);
 
 head.write(40);
jaw.write(60);
 reye.write(70);
 leye.write(10);
 brow.write(70);
 delay(1200);
 jaw.write(0);
 reye.write(40); //normal
 leye.write(40); //normal
brow.write(0);
delay(800);
  head.write(90);
 // END jaw move
 
 
 head.write(90);
// Lower head
digitalWrite(down, LOW);
delay(1500);
digitalWrite(down, HIGH);
headdoor.write(5);
delay(1000);
// Lower head end

// Raise head AGAIN
headdoor.write(85);
digitalWrite(up, LOW);
delay(1500);
digitalWrite(up, HIGH);
// Raise head end
playSdWav1.play("5b.WAV");
head.write(90);
jaw.write(60);
 reye.write(70);
 leye.write(10);
 brow.write(70);
 delay(1200);
 jaw.write(0);
 reye.write(40); //normal
 leye.write(40); //normal
brow.write(0);
 delay(500);

 // Lower head
digitalWrite(down, LOW);
delay(1500);
digitalWrite(down, HIGH);
headdoor.write(5);
// Lower head end
delay(600);
//Shut the switch off begin
handdoor.write(80);
hand.write(30);
delay(1000);
hand.write(76);
delay(200);
handdoor.write(0);
//Shut the switch off end
delay(500);


button = digitalRead(redswitch);
stepval=5;
time_now=millis();
m2_now=millis();
m1_now=millis();
 }

// End Step Five 5555555555555555555555555555555555555555555555555555555555555555 
    } //THIS IS THE END OF THE PROGRAM
