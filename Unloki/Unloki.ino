//"Unloki" by Vicarious aka Patrick Paumen

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Keyboard.h>
#include <avr/wdt.h>
 
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String uid = "0";

void setup(void) {
  Serial.begin(115200);
  Serial.println("NDEF Reader");
  nfc.begin();
  wdt_enable(WDTO_4S);
  Serial.println("reset");
}

void loop(void) {
  Serial.println("\nScan a NFC tag\n");
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read(); // Reads the RFID/NFC tag
    uid = tag.getUidString(); // Fetches UID from the tag and save it in variable "uid"
    Serial.println(uid); // Shows the UID of the scanned RFID/NFC tag in Serial Monitor
    /* RFID/NFC tag with 4 byte UID */
    if (uid == "01 23 AB CD") {
      Keyboard.print("Passphrase"); // Sends the string "Passphrase" to the computer
      Keyboard.write(KEY_RETURN); // Sends Enter
      delay(5000); //makes sure the password isn't repeated
    }
    /* RFID/NFC tag with 7 byte UID */
    else if (uid == "01 23 67 89 AB CD EF") {
      Keyboard.print("Hello, World!"); // Sends the string "Hello, World!" to the computer
      Keyboard.write(KEY_RETURN); // Sends Enter
      delay(5000); //makes sure the password isn't repeated
    }
    else {
      uid.replace(" ", "");
      uid.toLowerCase();
      Keyboard.print(uid);
      Keyboard.write(KEY_RETURN);
      delay(500);
    }
  }
  wdt_reset();
}
