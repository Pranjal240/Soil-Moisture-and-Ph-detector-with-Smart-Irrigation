#include <LiquidCrystal_I2C.h>

// LCD Address check karein (kabhi kabhi 0x27 ki jagah 0x3F hota hai)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int pumpPin = 2; // Pin number define kar diya readability ke liye

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  pinMode(pumpPin, OUTPUT);
  
  // Relay OFF state mein rakhe shuru mein (Assuming Active LOW Relay)
  digitalWrite(pumpPin, HIGH); 
  
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
  delay(2000); // Thoda wait karein system settle hone ke liye
  lcd.clear();
}

void loop() {
  int value = analogRead(A0);
  Serial.println(value);

  // RELAY CONTROL LOGIC
  // Agar mitti sookhi hai (value > 950)
  if (value > 950) {
    digitalWrite(pumpPin, LOW); // Pump ON (Active Low Relay)
    lcd.setCursor(0, 0);
    lcd.print("Pump: ON       "); // Spaces extra text ko clear karne ke liye
  } 
  else {
    digitalWrite(pumpPin, HIGH); // Pump OFF
    lcd.setCursor(0, 0);
    lcd.print("Pump: OFF      ");
  }

  // MOISTURE DISPLAY LOGIC
  lcd.setCursor(0, 1);
  if (value < 300) {
    lcd.print("Moist: HIGH    ");
  } else if (value >= 300 && value < 950) { // >= use karein overlap avoid karne ke liye
    lcd.print("Moist: MID     ");
  } else if (value >= 950) {
    lcd.print("Moist: LOW     ");
  }
  
  // IMPORTANT: Yeh delay add karein taaki relay baar-baar ON-OFF na ho
  delay(1000); 
}