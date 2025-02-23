/* Read RFID Tag with RC522 RFID Reader
 * Made by stJL with MIT License
 *
 * Feel free to use this code as you wish.
 * 請隨意使用此程式碼。
 */

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;      // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;      // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    // ... (Decimal and Hexadecimal output) ...

    if (rfid.uid.size == 4) {
      unsigned long uidDecimalReverse = 0;

      // Reverse Byte Order
      for (int i = 3; i >= 0; i--) {
        uidDecimalReverse = (uidDecimalReverse << 8) | rfid.uid.uidByte[i];
      }

      unsigned long shiftedValue = uidDecimalReverse >> 16;
      unsigned long remainder = uidDecimalReverse - (shiftedValue * 65536);

      Serial.print("Wiegand (Reverse shifted 16): ");
      Serial.print(shiftedValue);
      if (remainder < 10000){
        Serial.print("0");
      }
      if (remainder < 1000){
        Serial.print("0");
      }
      if (remainder < 100){
        Serial.print("0");
      }
      if (remainder < 10){
        Serial.print("0");
      }

      Serial.print(remainder);
      Serial.println();
    } else {
      Serial.println("Wiegand Conversion not implemented for this tag size");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
