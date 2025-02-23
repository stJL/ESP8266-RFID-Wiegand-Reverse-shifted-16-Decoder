# ESP8266 RFID Wiegand 解碼器 - 向右位移 16 位 (ESP8266 RFID Wiegand Decoder - Reverse shifted 16)

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

## 繁體中文說明 (Traditional Chinese Description)

本專案是一個 ESP8266 程式碼，用於讀取 RFID 標籤的唯一識別碼（UID），並嘗試逆向工程將其轉換為 34 位元 Wiegand 碼。Wiegand 碼廣泛應用於門禁系統，用於識別卡片或標籤。

### 專案目標 (Project Goals)

* 使用 ESP8266 讀取 RFID 標籤的 UID。
* 顯示 UID 的十進制和十六進制表示。
* 探索不同的字節順序和位移，以嘗試重建 Wiegand 碼。
* 提供一個實驗平台，用於研究 Wiegand 編碼。
* 詳細說明程式碼的推理和實踐過程，並強調門禁系統讀取方式的多樣性。

### 硬體需求 (Hardware Requirements)

* ESP8266 開發板 (例如：NodeMCU)
* RC522 RFID 讀取器
* RFID 標籤

### 接線 (Wiring)

將 RC522 RFID 讀取器連接到您的 ESP8266 開發板，接線方式如下：

* RC522 SDA (SS) -> ESP8266 D4 (GPIO2)
* RC522 SCK -> ESP8266 D5 (GPIO14)
* RC522 MOSI -> ESP8266 D7 (GPIO13)
* RC522 MISO -> ESP8266 D6 (GPIO12)
* RC522 RST -> ESP8266 D3 (GPIO0)
* RC522 3.3V -> ESP8266 3.3V
* RC522 GND -> ESP8266 GND

### 如何使用 (How to Use)

1.  在 Arduino IDE 中安裝 ESP8266 開發板支持。
2.  安裝 MFRC522 函式庫。
3.  將 `ESP8266_RFID_Wiegand_Decoder.ino` 程式碼上傳到您的 ESP8266 開發板。
4.  打開 Arduino 序列埠監視器，以查看 UID 和可能的 Wiegand 碼。
5.  將 RFID 標籤靠近 RC522 讀取器。

### 程式碼推理與實踐 (Code Reasoning and Practice)

1.  **UID 讀取與顯示：**
    * 程式碼使用 MFRC522 函式庫讀取 RFID 標籤的 UID。
    * UID 以十進制和十六進制格式顯示，方便查看原始數據。
      
2.  **Wiegand 碼逆向工程：**
    * 由於 Wiegand 編碼因系統而異，我們需要嘗試不同的字節順序和位移。
    * 程式碼首先嘗試正向和反向字節順序，並將結果以十進制顯示。
    * 接著，我們發現將反向字節順序的 UID 向右位移 16 位可以得到 Wiegand 碼的前半部分。
    * 通過計算位移後的餘數，我們重建了完整的 Wiegand 碼。
      
3.  **位移與餘數計算：**
    * 向右位移 16 位相當於除以 2^16 (65536)。
    * 位移後的結果是商，餘數是原始數據減去商乘以 65536。
    * 將商和餘數組合，即可得到完整的 Wiegand 碼。
      
4.  **門禁系統讀取方式的多樣性：**
    * **重要提示：** 門禁系統讀取 RFID 標籤的方式可能不同。除了向右位移 16 位，還可能存在以下位移方法：
        * **向左位移：** 某些系統可能使用向左位移，例如向左位移 8 位或 24 位。
        * **其他位移量：** 位移量不一定是 16 位，可能是其他數值，例如 10 位或 20 位。
        * **位元反轉：** 系統可能在位移前後對數據進行位元反轉。
        * **字節交換：** 系統可能在位移前後交換字節的順序。
    * 因此，您可能需要嘗試不同的位移方法和數據操作，才能找到與您的門禁系統相符的 Wiegand 碼。
      
5.  **重要提示：**
    * 本專案僅為調查工具，實際 Wiegand 編碼可能更複雜。
    * 為了獲得準確的 Wiegand 碼，您需要訪問控制系統的規格。
    * 本專案不包含奇偶校驗位計算。

### 貢獻 (Contributions)

歡迎任何形式的貢獻！如果您有任何改進建議或發現任何錯誤，請隨時提交 Pull Request 或 Issues。

### 授權 (License)

本專案使用 MIT 授權。詳細資訊請參閱 `LICENSE` 檔案。

---

## English Description

This project is an ESP8266 code that reads the Unique Identifier (UID) of an RFID tag and attempts to reverse engineer its conversion to a 34-bit Wiegand code. Wiegand codes are widely used in access control systems to identify cards or tags.

### Project Goals

* Read the UID of RFID tags using ESP8266.
* Display the decimal and hexadecimal representations of the UID.
* Explore different byte orders and bit shifts to attempt to reconstruct the Wiegand code.
* Provide an experimental platform for studying Wiegand encoding.
* Explain the reasoning and practice of the code in detail, emphasizing the diversity of access control system reading methods.

### Hardware Requirements

* ESP8266 Development Board (e.g., NodeMCU)
* RC522 RFID Reader
* RFID Tags

### Wiring

Connect the RC522 RFID reader to your ESP8266 development board as follows:

* RC522 SDA (SS) -> ESP8266 D4 (GPIO2)
* RC522 SCK -> ESP8266 D5 (GPIO14)
* RC522 MOSI -> ESP8266 D7 (GPIO13)
* RC522 MISO -> ESP8266 D6 (GPIO12)
* RC522 RST -> ESP8266 D3 (GPIO0)
* RC522 3.3V -> ESP8266 3.3V
* RC522 GND -> ESP8266 GND

### How to Use

1.  Install ESP8266 board support in Arduino IDE.
2.  Install the MFRC522 library.
3.  Upload the `ESP8266_RFID_Wiegand_Decoder.ino` code to your ESP8266 development board.
4.  Open the Arduino Serial Monitor to view the UID and possible Wiegand codes.
5.  Bring an RFID tag close to the RC522 reader.

### Code Reasoning and Practice

1.  **UID Reading and Display:**
    * The code uses the MFRC522 library to read the UID of RFID tags.
    * The UID is displayed in decimal and hexadecimal format for easy viewing of raw data.
      
2.  **Wiegand Code Reverse Engineering:**
    * Since Wiegand encoding varies between systems, we need to try different byte orders and bit shifts.
    * The code first tries forward and reverse byte orders, displaying the results in decimal.
    * Then, we found that right-shifting the reversed UID by 16 bits can get the first half of the Wiegand code.
    * By calculating the remainder after the shift, we reconstructed the full Wiegand code.
      
3.  **Bit Shift and Remainder Calculation:**
    * Right-shifting by 16 bits is equivalent to dividing by 2^16 (65536).
    * The shifted result is the quotient, and the remainder is the original data minus the quotient multiplied by 65536.
    * Combining the quotient and remainder gives the complete Wiegand code.
      
4.  **Diversity of Access Control System Reading Methods:**
    * **Important Note:** Access control systems may read RFID tags differently. Besides right-shifting by 16 bits, the following shift methods may exist:
        * **Left Shift:** Some systems may use left shifts, such as left-shifting by 8 or 24 bits.
        * **Other Shift Amounts:** The shift amount may not be 16 bits, but other values, such as 10 or 20 bits.
        * **Bit Reversal:** Systems may perform bit reversal on the data before or after shifting.
        * **Byte Swapping:** Systems may swap the order of bytes before or after shifting.
    * Therefore, you may need to try different shift methods and data manipulations to find the Wiegand code that matches your access control system.
      
5.  **Important Notes:**
    * This project is only an investigative tool, and real Wiegand encoding may be more complex.
    * To get accurate Wiegand codes, you need the specifications of your access control system.
    * This project does not include parity bit calculations.

### Contributions

Contributions of any kind are welcome! If you have any suggestions for improvement or find any bugs, please feel free to submit a Pull Request or Issues.

### License

This project is licensed under the MIT License. See the `LICENSE` file for details.
