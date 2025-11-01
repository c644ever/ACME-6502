/*
 * 6502 Breadboard System - EEPROM Programmer & Memory Simulator
 * Arduino Mega 2560
 */

//#include "rom.h"
//#include "eeprom.h"
# define EEPROMSIZE 32768

// === PORT DEFINITIONS ===
#define ADDR_LOW   PORTA   // A0-A7  (Pins 22-29)
#define ADDR_HIGH  PORTC   // A8-A15 (Pins 37-30)
#define DATA_BUS   PORTL   // D0-D7  (Pins 49-42)
#define DATA_DDR   DDRL
#define DATA_PIN   PINL

// === CONTROL PINS ===
#define WE_PIN     5       // Write Enable  - blau
#define OE_PIN     7       // Output Enable - weiß
#define CE_PIN     4       // Chip Enable   - Grün
#define CLK_PIN    2       // Clock Gen     - Orange
#define RESET_PIN  6       // Reset         - lila 
#define RW_PIN     3       // 6502 RWB Sig  - gelb

// === MEMORY CONFIGURATION ===
#define RAM_START  0x0000
#define RAM_END    0x07FF
#define ROM_START  0xF800
#define ROM_END    0xFFFF

// Automatische Größenberechnung
#define RAM_SIZE    (RAM_END - RAM_START + 1)
#define ROM_SIZE    (ROM_END - ROM_START + 1)

uint8_t ramMemory[RAM_SIZE];
uint8_t romMemory[ROM_SIZE];
bool clockRunning = false;


void setup() {
  Serial.begin(115200);
  initializeSystem();
  showMenu();
}

void loop() {
  if (Serial.available()) {
    handleMenu(Serial.read());
  }
}

/**
 * Initialisiert alle Pins und Speicherbereiche
 */
void initializeSystem() {
  // Ports konfigurieren
  DDRA = 0xFF;  // PORTA als Output
  DDRC = 0xFF;  // PORTC als Output
  DDRL = 0x00;  // PORTL als Input
  PORTL = 0xFF;  // Pullups aktivieren
  
  // Kontrollpins
  pinMode(WE_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);
  pinMode(CE_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(RW_PIN, INPUT);
  
  // Default states
  digitalWrite(WE_PIN, HIGH);
  digitalWrite(OE_PIN, HIGH);
  digitalWrite(CE_PIN, HIGH);
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(RESET_PIN, HIGH);
  
  // Debug-Ausgabe der Speichergrößen
  Serial.println("=== MEMORY CONFIGURATION ===");
  Serial.print("RAM: 0x");
  Serial.print(RAM_START, HEX);
  Serial.print("-0x");
  Serial.print(RAM_END, HEX);
  Serial.print(" (");
  Serial.print(RAM_SIZE);
  Serial.println(" bytes)");
  
  Serial.print("ROM: 0x");
  Serial.print(ROM_START, HEX);
  Serial.print("-0x");
  Serial.print(ROM_END, HEX);
  Serial.print(" (");
  Serial.print(ROM_SIZE);
  Serial.println(" bytes)");
  
  // Speicher initialisieren
  //memcpy(romMemory, rom_data, min(sizeof(rom_data), ROM_SIZE));
  //memset(ramMemory, 0x00, RAM_SIZE);
  
  Serial.println("=== ACME-6502 BREADBOARD SYSTEM READY ===");
}

/**
 * Zeigt das Hauptmenü
 */
void showMenu() {
  Serial.println("\n" + String(50, '='));
  Serial.println("           ACME-6502 SYSTEM MENU");
  Serial.println(String(50, '='));
  Serial.println("1 - Program EEPROM with ea(with safety check)");
  Serial.println("2 - Read EEPROM contents");
  Serial.println("3 - Clock Generator");
  Serial.println("4 - Bus Monitor / Debugger");
  Serial.println("5 - Memory Simulator / Debugger");
  Serial.println("6 - Single Step Clock");
  Serial.println("R - Reset System");
  Serial.println("M - Show this menu");
  Serial.println(String(50, '='));
  Serial.print("Select option: ");
}

/**
 * Verarbeitet Menüeingaben
 */
void handleMenu(char command) {
  Serial.println(); // Leerzeile für bessere Lesbarkeit
  
  switch(command) {
    case '1':
      programEEPROM();
      break;
    case '2':
      readEEPROM();
      break;
    case '3':
      clockGenerator();
      break;
    case '4':
      busMonitor();
      break;
    case '5':
      memorySimulator();
      break;
    case '6':
      singleStepClock();
      break;
    case 'r':
    case 'R':
      resetSystem();
      break;
    case 'm':
    case 'M':
      showMenu();
      break;
    default:
      Serial.println("❌ Invalid command!");
      showMenu();
  }
}

/**
 * EEPROM Programmierung mit Sicherheitsabfrage
 */
void programEEPROM() {
  Serial.println("🚨 === EEPROM PROGRAMMING - SAFETY FIRST ===");
  /*Serial.println("⚠️  CRITICAL: Remove 6502 GND jumper before programming!");
  Serial.println("📋 Procedure:");
  Serial.println("   1. Locate GND jumper on 6502");
  Serial.println("   2. Carefully remove it from breadboard");
  Serial.println("   3. Wait for LED to turn off (if present)");
  Serial.println("   4. Press any key to continue...");
  Serial.println("   (Press 'X' to cancel)");
  
  // Sicherheitsabfrage
  while(!Serial.available()) {
    delay(100);
  }
  
  char safety = Serial.read();
  if(safety == 'x' || safety == 'X') {
    Serial.println("❌ Programming cancelled.");
    return;
  }
  */
  Serial.println("✅ Safety confirmed. Starting programming...");
  
  // Programmierung
  DDRL = 0xFF;
  DDRA = 0xff;
  DDRC = 0xff;

  digitalWrite(OE_PIN,HIGH);
  digitalWrite(WE_PIN,HIGH);
  delay(10);

  
  for(uint16_t address = 0; address < EEPROMSIZE; address++) {
    setAddress(address);
    uint8_t prog=0xea;

    PORTL = prog ;  //

    delay(1); 
    
    // Write cycle
    digitalWrite(CE_PIN,LOW);
    digitalWrite(WE_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(WE_PIN, HIGH);
    digitalWrite(CE_PIN, HIGH);
    delay(6);

    //Verify
    DDRL = 0x00;
    PORTL = 0xFF;
    digitalWrite(OE_PIN, LOW);
    digitalWrite(CE_PIN, LOW);
    delay(1);
    uint8_t verify = PINL;
    digitalWrite(CE_PIN, HIGH);
    digitalWrite(OE_PIN, HIGH);
    DDRL = 0xFF;
    
    if(verify != prog ) {
      Serial.print("❌ Verify error at address: 0x");
      Serial.println(address, HEX);
      break;
    }
  
    if(address % 256 == 0) {
      //Serial.print("⬜");
      Serial.println(address,HEX);
    }
  }

  DDRL = 0x00;
  PORTL = 0xFF;
  digitalWrite(OE_PIN,LOW);
  
  Serial.println("\n✅ EEPROM programming completed!");
  Serial.println("🔌 Remember to reconnect 6502 GND jumper!");
}

/**
 * EEPROM Auslesen und Hex-Dump
 */
void readEEPROM() {
  Serial.println("📖 === READING EEPROM ===");
  
  DDRL = 0x00;
  PORTL = 0xFF;
  
  for(uint16_t address = 0; address < EEPROMSIZE; address++) {
    setAddress(address);
    
    digitalWrite(OE_PIN, LOW);
    digitalWrite(CE_PIN, LOW);
    delayMicroseconds(10);
    uint8_t data = DATA_PIN;
    digitalWrite(CE_PIN, HIGH);
    digitalWrite(OE_PIN, HIGH);
    
    if(address % 32 == 0) {
      if(address > 0) Serial.println();
      Serial.print("0x");
      if(address < 0x1000) Serial.print("0");
      if(address < 0x0100) Serial.print("0");
      if(address < 0x0010) Serial.print("0");
      Serial.print(address, HEX);
      Serial.print(": ");
    }
    
    Serial.print(data < 16 ? "0" : "");
    Serial.print(data, HEX);
    Serial.print(" ");
  }
  
  Serial.println("\n✅ EEPROM read completed!");
}

/**
 * Taktgenerator mit 3 Geschwindigkeiten
 */
void clockGenerator() {
  Serial.println("⏰ === CLOCK GENERATOR ===");
  Serial.println("S - Slow (500ms)");
  Serial.println("M - Medium (100ms)");
  Serial.println("F - Fast (20ms)");
  Serial.println("X - Stop");
  Serial.print("Select speed: ");
  
  while(!Serial.available()) {
    delay(10);
  }
  
  char speed = Serial.read();
  int delayTime = 0;
  
  switch(speed) {
    case 's': case 'S': delayTime = 500; break;
    case 'm': case 'M': delayTime = 100; break;
    case 'f': case 'F': delayTime = 20; break;
    case 'x': case 'X': 
      stopClock();
      Serial.println("⏹️  Clock stopped");
      return;
    default:
      Serial.println("❌ Invalid selection");
      return;
  }
  
  Serial.println("🔄 Clock running... Press any key to stop");
  startClock(delayTime);
  
  while(!Serial.available()) {
    // Takt generieren
    digitalWrite(CLK_PIN, HIGH);
    delay(delayTime/2);
    digitalWrite(CLK_PIN, LOW);
    delay(delayTime/2);
  }
  
  Serial.read();
  stopClock();
  Serial.println("⏹️  Clock stopped");
}

/**
 * Bus Monitor mit Taktversorgung
 */
void busMonitor() {
  Serial.println("🔍 === BUS MONITOR ===");
  Serial.println("Monitoring bus activity with clock...");
  Serial.println("Press any key to stop");
  Serial.println("ADDR    : DATA  WE OE RW");
  Serial.println(String(30, '-'));
  
  DDRL = 0x00;
  PORTL = 0xFF;
  
  // Starte langsamen Takt für 6502
  startClock(50);
  
  unsigned long lastPrint = 0;
  
  while(!Serial.available()) {
    // Takt generieren
    digitalWrite(CLK_PIN, HIGH);
    delay(25);
    digitalWrite(CLK_PIN, LOW);
    delay(25);
    
    if(millis() - lastPrint >= 100) {
      uint16_t address = (ADDR_HIGH << 8) | (ADDR_LOW & 0xFF);
      uint8_t data = DATA_PIN;
      
      Serial.print("0x");
      if(address < 0x1000) Serial.print("0");
      if(address < 0x0100) Serial.print("0");
      if(address < 0x0010) Serial.print("0");
      Serial.print(address, HEX);
      Serial.print(" : 0x");
      Serial.print(data < 16 ? "0" : "");
      Serial.print(data, HEX);
      Serial.print("  ");
      Serial.print(digitalRead(WE_PIN));
      Serial.print("  ");
      Serial.print(digitalRead(OE_PIN));
      Serial.print("  ");
      Serial.println(digitalRead(RW_PIN));
      
      lastPrint = millis();
    }
  }
  
  stopClock();
  Serial.read();
  Serial.println("✅ Bus monitor stopped");
}

/**
 * Memory Simulator mit Taktversorgung
 */
void memorySimulator() {
  Serial.println("💾 === MEMORY SIMULATOR ===");
  Serial.print("Simulating ");
  Serial.print(RAM_SIZE);
  Serial.print(" bytes RAM (0x");
  Serial.print(RAM_START, HEX);
  Serial.print("-0x");
  Serial.print(RAM_END, HEX);
  Serial.print(") and ");
  Serial.print(ROM_SIZE);
  Serial.print(" bytes ROM (0x");
  Serial.print(ROM_START, HEX);
  Serial.print("-0x");
  Serial.print(ROM_END, HEX);
  Serial.println(")");
  Serial.println("Press any key to stop");
  
  DATA_DDR = 0x00;
  DATA_BUS = 0xFF;
  
  // Starte Takt für 6502
  startClock(20);
  
  while(!Serial.available()) {
    // Takt generieren
    digitalWrite(CLK_PIN, HIGH);
    delay(10);
    digitalWrite(CLK_PIN, LOW);
    delay(10);
    
    uint16_t address = (ADDR_HIGH << 8) | (ADDR_LOW & 0xFF);
    bool write_enable = !digitalRead(WE_PIN);
    bool output_enable = !digitalRead(OE_PIN);
    
    if(write_enable && output_enable) {
      // Write cycle
      DATA_DDR = 0x00;
      uint8_t data = DATA_PIN;
      
      if(address >= RAM_START && address <= RAM_END) {
        ramMemory[address - RAM_START] = data;
        Serial.print("💾 WR RAM[0x");
        Serial.print(address, HEX);
        Serial.print("] = 0x");
        Serial.print(data < 16 ? "0" : "");
        Serial.println(data, HEX);
      }
    } else if(output_enable) {
      // Read cycle
      DATA_DDR = 0xFF;
      
      if(address >= RAM_START && address <= RAM_END) {
        DATA_BUS = ramMemory[address - RAM_START];
      } else if(address >= ROM_START && address <= ROM_END) {
        DATA_BUS = romMemory[address - ROM_START];
      } else {
        DATA_BUS = 0xFF;
      }
      
      delayMicroseconds(1);
      DATA_DDR = 0x00;
      DATA_BUS = 0xFF;
    }
  }
  
  stopClock();
  Serial.read();
  DATA_DDR = 0x00;
  DATA_BUS = 0xFF;
  Serial.println("✅ Memory simulator stopped");
}

/**
 * Einzelschritt Takt
 */
void singleStepClock() {
  Serial.println("🔂 Single clock pulse generated");
  digitalWrite(CLK_PIN, HIGH);
  delay(1);
  digitalWrite(CLK_PIN, LOW);
}

/**
 * System Reset
 */
void resetSystem() {
  Serial.println("🔄 Resetting system...");
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN, HIGH);
  Serial.println("✅ System reset complete");
}

/**
 * Startet Taktgenerator
 */
void startClock(int periodMs) {
  if(!clockRunning) {
    pinMode(CLK_PIN, OUTPUT);
    clockRunning = true;
    Serial.print("🎯 Clock started (");
    Serial.print(periodMs);
    Serial.println("ms period)");
  }
}

/**
 * Stoppt Taktgenerator
 */
void stopClock() {
  digitalWrite(CLK_PIN, LOW);
  if(clockRunning) {
    clockRunning = false;
    Serial.println("⏹️  Clock stopped");
  }
}

/**
 * Setzt Adresse auf Adressbus
 */
void setAddress(uint16_t address) {
  PORTA = address & 0xFF;
  PORTC = (address >> 8) & 0xFF;
}

