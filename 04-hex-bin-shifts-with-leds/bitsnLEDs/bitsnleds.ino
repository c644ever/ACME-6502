/*
 * Port L LED Test - Linear Version for Beginners
 * This program tests 8 LEDs connected to Arduino pins 42-49
 */

// SETUP: Runs ONE TIME when Arduino starts or resets
void setup() {
  Serial.begin(9600);  // Start communication with computer at 9600 bits per second
  
  /* BINARY EXPLANATION:
   * B11111111 means: 1 1 1 1 1 1 1 1
   * Each "1" sets a pin as OUTPUT:
   * Pin 42=OUTPUT, 43=OUTPUT, 44=OUTPUT...49=OUTPUT
   */
  DDRL = B11111111;  // Set all Port L pins as OUTPUT
  
  /* BINARY EXPLANATION:  
   * B00000000 means: 0 0 0 0 0 0 0 0
   * Each "0" turns an LED OFF:
   * Pin 42=OFF, 43=OFF, 44=OFF...49=OFF
   */
  PORTL = B00000000; // Turn all LEDs off initially
  
  Serial.println("\n=== Port L LED Connection Test ===");
  Serial.println("Testing Knight Rider scanner first...");
  delay(1000);  // Wait 1 second before starting
}

// LOOP: Runs FOREVER, repeating over and over
void loop() {
  // =================================================================
  // PART 1: Knight Rider Scanner (like the car in the TV show)
  // =================================================================
  Serial.println("\n--- Knight Rider Scan ---");
  Serial.println("You should see a light moving back and forth");
  
  /* FOR LOOP EXPLANATION:
   * for(int i = 0; i < 8; i++) means:
   * - Start with i = 0
   * - Keep going as long as i < 8
   * - After each loop, increase i by 1 (i++)
   * So: i=0,1,2,3,4,5,6,7 (8 times total)
   */
  
  // Move light left to right
  for (int i = 0; i < 8; i++) {
    /* BIT SHIFTING EXPLANATION:
     * (1 << i) means "take number 1 and shift its bits left i times"
     * When i=0: 00000001 << 0 = 00000001 (LED 0 lights up)
     * When i=1: 00000001 << 1 = 00000010 (LED 1 lights up)  
     * When i=2: 00000001 << 2 = 00000100 (LED 2 lights up)
     * ...
     * When i=7: 00000001 << 7 = 10000000 (LED 7 lights up)
     */
    PORTL = (1 << i);  // Light moves one position each time
    delay(150);  // Wait 150 milliseconds (0.15 seconds)
  }
  
  // Move light right to left (skip the ends to avoid duplicate)
  for (int i = 6; i > 0; i--) {
    /* FOR LOOP EXPLANATION:
     * for(int i = 6; i > 0; i--) means:
     * - Start with i = 6
     * - Keep going as long as i > 0  
     * - After each loop, decrease i by 1 (i--)
     * So: i=6,5,4,3,2,1 (6 times total)
     */
    PORTL = (1 << i);  // Light moves back
    delay(150);
  }
  
  PORTL = B00000000;  // Turn all LEDs off
  delay(500);  // Wait half second
  
  
  // =================================================================
  // PART 2: Alternating Pattern Test
  // =================================================================
  Serial.println("\n--- Test 1: Alternating Pattern ---");
  
  /* HEXADECIMAL EXPLANATION:
   * 0x55 is a HEX number. Hex is base-16:
   * Digits: 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
   * 0x55 in binary = 01010101
   * Each hex digit = 4 bits: 5=0101, 5=0101 → 01010101
   */
  
  // Pattern 1: Alternating bits (0x55 = 01010101)
  Serial.println("Pattern 1: 0x55 (B01010101)");
  Serial.println("This should light: PL7, PL5, PL3, PL1");
  Serial.println("Which are pins:    43,  45,  47,  49");
  
  PORTL = 0x55;  // Same as B01010101 - every other LED on
  delay(1000);   // Show pattern for 1 second
  
  // Ask question about this pattern
  Serial.print("Are LEDs on pins 43,45,47,49 lit? (y/n): ");
  
  /* WHILE LOOP EXPLANATION:
   * while(!Serial.available()) means:
   * "Keep looping as long as NO data is available from Serial"
   * The program STOPS here and waits for you to type something
   */
  while (!Serial.available()) {
    // Empty loop - just wait for user input
  }
  
  // Read what the user typed
  String response1 = Serial.readString();
  response1.trim();  // Remove spaces and newlines
  
  // Check if answer was "y" (yes)
  if (response1 != "y") {
    Serial.println("⚠️  Check your wiring! The pattern doesn't match.");
  } else {
    Serial.println("✓ Connection verified!");
  }
  
  // Clear any extra characters from serial buffer
  while (Serial.available()) { 
    Serial.read(); 
  }
  delay(1000);  // Wait 1 second
  
  /* HEXADECIMAL EXPLANATION:
   * 0xAA in binary = 10101010
   * Each hex digit = 4 bits: A=1010, A=1010 → 10101010
   * A in hex = 10 in decimal = 1010 in binary
   */
  
  // Pattern 2: Opposite alternating (0xAA = 10101010)
  Serial.println("Pattern 2: 0xAA (B10101010)");
  Serial.println("This should light: PL6, PL4, PL2, PL0");
  Serial.println("Which are pins:    42,  44,  46,  48");
  PORTL = 0xAA;  // Same as B10101010 - opposite pattern from before
  delay(1000);   // Show pattern for 1 second
  
  // Ask question about this pattern
  Serial.print("Are LEDs on pins 42,44,46,48 lit? (y/n): ");
  while (!Serial.available()) {
    // Wait for user input - program STOPS here until you answer
  }
  String response2 = Serial.readString();
  response2.trim();
  if (response2 != "y") {
    Serial.println("⚠️  Check your wiring! The pattern doesn't match.");
  } else {
    Serial.println("✓ Connection verified!");
  }
  
  // Clear serial buffer
  while (Serial.available()) { 
    Serial.read(); 
  }
  
  PORTL = B00000000;  // Turn all LEDs off
  delay(500);         // Wait half second
  
  
  // =================================================================
  // PART 3: Single LED Test - Testing each LED one by one
  // =================================================================
  Serial.println("\n--- Test 2: Single LEDs ---");
  
  /* BINARY PATTERN EXPLANATION:
   * We test each LED with these patterns:
   * B00000001 = Only rightmost LED (tests pin 49)
   * B00000010 = Only second LED (tests pin 48)  
   * B00000100 = Only third LED (tests pin 47)
   * ...
   * B10000000 = Only leftmost LED (tests pin 42)
   */
  
  // Test LED on pin 49 (PL0) - Rightmost LED
  Serial.println("Testing pin 49 (PL0) - Rightmost LED");
  PORTL = B00000001;  // Only first LED on - binary 00000001
  delay(800);         // Wait 0.8 seconds so you can see it
  
  Serial.print("Is this LED lit? (y/n): ");
  while (!Serial.available()) {}  // Wait for answer
  String response3 = Serial.readString();
  if (response3 != "y") {
    Serial.println("⚠️  Check connection for pin 49");
  }
  while (Serial.available()) { 
    Serial.read();  // Clear buffer
  }
  PORTL = B00000000;  // Turn off
  delay(300);         // Brief pause
  
  // Test LED on pin 48 (PL1) - Second from right
  Serial.println("Testing pin 48 (PL1)");
  PORTL = B00000010;  // Only second LED on - binary 00000010
  delay(800);
  Serial.print("Is this LED lit? (y/n): ");
  while (!Serial.available()) {}  // Wait for answer
  String response4 = Serial.readString();
  if (response4 != "y") {
    Serial.println("⚠️  Check connection for pin 48");
  }
  while (Serial.available()) { 
    Serial.read();  // Clear buffer
  }
  PORTL = B00000000;  // Turn off
  delay(300);
  
  // Test LED on pin 47 (PL2) - Third from right
  Serial.println("Testing pin 47 (PL2)");
  PORTL = B00000100;  // Only third LED on - binary 00000100
  delay(800);
  Serial.print("Is this LED lit? (y/n): ");
  while (!Serial.available()) {}  // Wait for answer
  String response5 = Serial.readString();
  if (response5 != "y") {
    Serial.println("⚠️  Check connection for pin 47");
  }
  while (Serial.available()) { 
    Serial.read();  // Clear buffer
  }
  PORTL = B00000000;  // Turn off
  delay(300);
  
  // ... (this continues for all 8 LEDs in the same pattern)
  
  // Test LED on pin 42 (PL7) - Last one (leftmost)
  Serial.println("Testing pin 42 (PL7) - Leftmost LED");
  PORTL = B10000000;  // Only last LED on - binary 10000000
  delay(800);
  Serial.print("Is this LED lit? (y/n): ");
  while (!Serial.available()) {}  // Wait for answer
  String response10 = Serial.readString();
  if (response10 != "y") {
    Serial.println("⚠️  Check connection for pin 42");
  }
  while (Serial.available()) { 
    Serial.read();  // Clear buffer
  }
  PORTL = B00000000;  // Turn all off
  delay(300);
  
  
  // =================================================================
  // PART 4: Binary Counting Demo - Watch numbers count in binary!
  // =================================================================
  Serial.println("\n--- Test 3: Binary Counting ---");
  Serial.println("Watch the LEDs count in binary from 0 to 15");
  Serial.println("Rightmost 4 LEDs show the binary number");
  Serial.println("Example: 5 in binary = 0101 (LEDs 2 and 0 on)");
  delay(2000);  // Wait 2 seconds to read the message
  
  /* BINARY COUNTING EXPLANATION:
   * We count from 0 to 15, which in 4-bit binary is:
   * 0=0000, 1=0001, 2=0010, 3=0011, 4=0100, ... 15=1111
   * The rightmost 4 LEDs (pins 49,48,47,46) show the count
   */
  for (int i = 0; i < 16; i++) {
    PORTL = i;  // Set LEDs to show the binary version of number i
    
    Serial.print("Binary: ");
    
    // Print the binary pattern so you can see what it should be
    for (int bitPos = 7; bitPos >= 0; bitPos--) {
      /* BIT READING EXPLANATION:
       * (PORTL & (1 << bitPos)) checks if a specific bit is 1 or 0
       * It compares PORTL with a pattern that has only one 1 bit
       * If both have 1 in that position, result is not zero (true)
       */
      if (PORTL & (1 << bitPos)) {
        Serial.print("1");  // LED should be ON
      } else {
        Serial.print("0");  // LED should be OFF
      }
    }
    Serial.print("  Decimal: ");
    Serial.println(i);
    delay(600);  // Wait 0.6 seconds between numbers
  }
  
  PORTL = B00000000;  // Turn all LEDs off
  delay(1000);        // Wait 1 second
  
  Serial.println("\nAll tests complete! Starting over...");
  delay(3000);  // Wait 3 seconds before starting the loop again
}

/* =================================================================
   SUMMARY OF KEY CONCEPTS:

   1. BINARY NUMBERS: Base-2 system using only 0s and 1s
      - Each position is a power of 2
      - B1010 = (1×8) + (0×4) + (1×2) + (0×1) = 10
   
   2. HEXADECIMAL NUMBERS: Base-16 system (0-9, A-F)
      - More compact than binary
      - 0x5A = (5×16) + (10×1) = 90
      - Each hex digit = 4 binary bits
   
   3. BIT SHIFTING: Moving bits left or right
      - 00000001 << 2 = 00000100 (moves 1 two positions left)
      - 00110000 >> 3 = 00000110 (moves bits three positions right)
   
   4. FOR LOOPS: Repeat code a specific number of times
      - for(int i=0; i<5; i++) runs 5 times (i=0,1,2,3,4)
      - for(int i=10; i>0; i--) counts down from 10 to 1
   
   5. PROGRAM FLOW:
      - setup() runs once at start
      - loop() runs forever, repeating the entire sequence
      - Each action happens in order from top to bottom
================================================================= */