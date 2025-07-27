# remote_switch
Source code for an ESP8266 driving a PN2222 to act like a IoT remote switch

## Build and Flash
```bash
arduino-cli compile --fqbn esp8266:esp8266:generic . && arduino-cli upload -p /dev/ttyACM0 --fqbn esp8266:esp8266:generic .
```

## Monitor Serial Output
```bash
arduino-cli monitor -p /dev/ttyACM0 --config baudrate=115200
```