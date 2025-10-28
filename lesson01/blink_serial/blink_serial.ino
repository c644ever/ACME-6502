// Let the builin LED Blink and make some serial output

#define LED	13

void setup (void)
{
	pinMode(LED,OUTPUT);		// Pin 13 which is connected to the onboard LED as OUTPUT
	Serial.begin(115200);		// Begin serial communication with 115200 bits per second 
}

void loop ( void )
{
	digitalWrite(LED,HIGH);		//switch the LED on
	Serial.println ( "LED on");	//tell this over serial
	delay(500);			//wait 500 milliseconds

	digitalWrite(LED,LOW);		//you find out yourself ;-)
	Serial.println ("LED off");
	delay(500);
}
