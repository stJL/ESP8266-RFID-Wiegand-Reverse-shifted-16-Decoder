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
    Serial.print("Decimal: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i]);
      if (i < rfid.uid.size - 1) {
        Serial.print(", "); // Add comma if not the last byte
      }
    }
    Serial.println(); // Newline after decimal output

    Serial.print("Hexadecimal: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      if (rfid.uid.uidByte[i] < 0x10) {
        Serial.print("0"); // Pad with leading zero if needed
      }
      Serial.print(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) {
        Serial.print(" "); // Add space if not the last byte
      }
    }
    Serial.println(); // Newline after hexadecimal output

    if (rfid.uid.size == 4) {
      unsigned long uidDecimalForward = 0;
      unsigned long uidDecimalReverse = 0;

      // Forward Byte Order
      for (int i = 0; i < 4; i++) {
        uidDecimalForward = (uidDecimalForward << 8) | rfid.uid.uidByte[i];
      }

      // Reverse Byte Order
      for (int i = 3; i >= 0; i--) {
        uidDecimalReverse = (uidDecimalReverse << 8) | rfid.uid.uidByte[i];
      }

      Serial.print("Wiegand (Forward): ");
      Serial.print(uidDecimalForward);
      Serial.println();

      Serial.print("Wiegand (Reverse): ");
      Serial.print(uidDecimalReverse);
      Serial.println();

      // Example of bit shifting.
      Serial.print("Wiegand (Forward shifted 1): ");
      Serial.print(uidDecimalForward >> 1);
      Serial.println();

      Serial.print("Wiegand (Reverse shifted 1): ");
      Serial.print(uidDecimalReverse >> 1);
      Serial.println();

      // Example of bit shifting.
      Serial.print("Wiegand (Forward shifted 8): ");
      Serial.print(uidDecimalForward >> 8);
      Serial.println();

      Serial.print("Wiegand (Reverse shifted 8): ");
      Serial.print(uidDecimalReverse >> 8);
      Serial.println();

      // Example of bit shifting.
      Serial.print("Wiegand (Forward shifted 16): ");
      Serial.print(uidDecimalForward >> 16);
      Serial.println();

      // Important: Display the partial match
      Serial.print("Wiegand (Reverse shifted 16): ");
      Serial.print(uidDecimalReverse >> 16);
      Serial.println();

      // Reconstruct the full Wiegand number
      Serial.print("Wiegand (Reverse shifted 16, reconstructed): ");
      unsigned long shiftedValue = uidDecimalReverse >> 16;
      unsigned long remainder = uidDecimalReverse - (shiftedValue * 65536);

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
