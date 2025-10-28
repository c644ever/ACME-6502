//

#define LED	13

void setup (void)
{
	pinMode(LED,OUTPUT);
	Serial.begin(115200);
}

void loop ( void )
{
	digitalWrite(LED,HIGH);
	Serial.println ( "LED an");
	delay(500);

	digitalWrite(LED,LOW);
	Serial.println ("LED aus");
	delay(500);
}
