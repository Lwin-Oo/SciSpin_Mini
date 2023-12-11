void motorReset()
{
  digitalWrite(EN_PIN, HIGH);
  int interval = 200;
  int microstep = 256;
  driver.microsteps(microstep);
  saveSettings();
}

void readSettings()
{
  int address = 0;
  interval = (EEPROM.read(address) << 8) + EEPROM.read(address + 1);

  if (interval == 0)
  {
    interval = 200;
  }
}

void saveSettings()
{
  int address = 0;

  EEPROM.write(address, interval >> 8);
  EEPROM.write(address + 1, interval & 0xFF);
}

void beep()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1);
  digitalWrite(LED_BUILTIN, LOW);
}

void longBeep()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(20);
  digitalWrite(LED_BUILTIN, LOW);
}

void startup() {
  for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(80);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

  colorWipe(strip.Color(0, 0, 0, 0), 1);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
