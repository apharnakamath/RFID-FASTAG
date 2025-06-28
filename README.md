# RFID FASTag Toll Gate System

An Arduino-based automated toll gate system that uses RFID technology to simulate FASTag payments. The system detects vehicles using an ultrasonic sensor, reads RFID tags, and controls a servo motor to operate the toll gate barrier.

## Features

- **Automatic Vehicle Detection**: Ultrasonic sensor detects approaching vehicles
- **RFID Tag Reading**: RC522 RFID reader processes FASTag cards
- **Automated Gate Control**: Servo motor operates the toll gate barrier
- **Visual Feedback**: LED indicators show system status
- **IR Sensor Integration**: Additional proximity detection capability
- **Real-time Processing**: Immediate response to valid RFID tags

## Hardware Components

| Component | Quantity | Description |
|-----------|----------|-------------|
| Arduino UNO | 1 | Main microcontroller |
| RC522 RFID Reader | 1 | 13.56MHz RFID module |
| HC-SR04 Ultrasonic Sensor | 1 | Distance measurement |
| SG90 Servo Motor | 1 | Gate barrier control |
| IR Sensor | 1 | Additional proximity detection |
| LEDs | 2-3 | Status indicators |
| Resistors | 3 | 220Ω for LEDs |
| Breadboard/PCB | 1 | Circuit assembly |
| Jumper Wires | Various | Connections |
| RFID Tags/Cards | Multiple | FASTag simulation |

## Circuit Connections

### Arduino UNO Pin Assignments

#### RC522 RFID Reader
- **VCC** → 3.3V
- **RST** → Digital Pin 9
- **GND** → GND
- **MISO** → Digital Pin 12
- **MOSI** → Digital Pin 11
- **SCK** → Digital Pin 13
- **SDA** → Digital Pin 10

#### HC-SR04 Ultrasonic Sensor
- **VCC** → 5V
- **TRIG** → Digital Pin 7
- **ECHO** → Digital Pin 6
- **GND** → GND

#### SG90 Servo Motor
- **VCC** → 5V
- **GND** → GND
- **PWM** → Digital Pin 5

#### IR Sensor
- **VCC** → 5V
- **OUT** → Digital Pin 8
- **GND** → GND

#### Status LEDs
- **Green LED** → Digital Pin 2 (with 220Ω resistor)
- **Red LED** → Digital Pin 3 (with 220Ω resistor)
- **Blue LED** → Digital Pin 4 (with 220Ω resistor)

## Software Requirements

### Arduino Libraries
```cpp
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
```

### Installation
1. Install Arduino IDE
2. Install required libraries:
   - MFRC522 Library (by GithubCommunity)
   - Servo Library (built-in)
   - SPI Library (built-in)

## How It Works

### System Flow
1. **Vehicle Detection**: Ultrasonic sensor detects approaching vehicle
2. **RFID Scanning**: System activates RFID reader
3. **Tag Validation**: Checks if RFID tag is authorized
4. **Gate Operation**: 
   - Valid tag → Gate opens (servo rotates)
   - Invalid tag → Gate remains closed
5. **Status Display**: LEDs indicate transaction status
6. **Auto-Close**: Gate closes after predetermined time

### State Machine
```
IDLE → VEHICLE_DETECTED → RFID_SCAN → VALIDATE → GATE_OPEN → GATE_CLOSE → IDLE
```

## Usage

### Setup
1. Assemble circuit according to connection diagram
2. Upload Arduino code to the board
3. Power on the system
4. Place RFID tags near the reader to register them

### Operation
1. Approach the toll gate with a vehicle (simulate with hand/object)
2. Present RFID tag to the reader
3. Gate opens for valid tags
4. Gate automatically closes after 3-5 seconds

### LED Status Indicators
- **Green**: Valid RFID tag detected, gate opening
- **Red**: Invalid RFID tag or system error
- **Blue**: System ready/standby mode

## Code Structure

### Main Functions
- `setup()`: Initialize components and serial communication
- `loop()`: Main program execution
- `readRFID()`: Handle RFID tag reading
- `controlGate()`: Manage servo motor operation
- `checkDistance()`: Process ultrasonic sensor data

### Key Variables
- `authorizedTags[]`: Array of valid RFID tag UIDs
- `gatePosition`: Current servo motor angle
- `detectionDistance`: Ultrasonic sensor threshold

## Customization

### Adding New RFID Tags
```cpp
String authorizedTags[] = {
    "XX XX XX XX",  // Add new tag UID here
    "YY YY YY YY",
    // ... more tags
};
```

### Adjusting Detection Distance
```cpp
const int DETECTION_THRESHOLD = 10; // Distance in cm
```

### Gate Timing
```cpp
const int GATE_OPEN_TIME = 5000; // Time in milliseconds
```

## Troubleshooting

### Common Issues

**RFID Not Reading:**
- Check SPI connections (MISO, MOSI, SCK)
- Verify 3.3V power supply to RC522
- Ensure proper SDA connection

**Servo Not Moving:**
- Confirm PWM pin connection
- Check 5V power supply
- Verify servo library inclusion

**Ultrasonic Sensor Issues:**
- Check TRIG and ECHO pin connections
- Ensure stable 5V power
- Verify timing in code

**Serial Monitor Output:**
```
System Initialized
Vehicle Detected: 8 cm
RFID Tag: A1 B2 C3 D4
Access Granted - Gate Opening
Gate Closed
```

## Safety Considerations

- Use appropriate power supply ratings
- Ensure stable connections to prevent intermittent failures
- Add debouncing for sensor inputs
- Implement emergency manual override
- Consider adding timeout mechanisms

## Applications

- **Educational Projects**: Learn RFID and IoT concepts
- **Prototype Development**: Toll gate system simulation
- **Access Control**: Adapt for building entry systems
- **Parking Management**: Vehicle access control
- **Industrial Automation**: Material handling gates

## Future Enhancements

- **Database Integration**: Store transaction records
- **Wireless Communication**: WiFi/Bluetooth connectivity
- **Display Module**: LCD/OLED for user feedback
- **Multiple Lane Support**: Expand to multiple gates
- **Mobile App**: Remote monitoring and control
- **Payment Integration**: Real payment processing
- **Camera Module**: Vehicle number plate recognition

## Project Photos

The system includes:
- Clean breadboard layout with organized wiring
- Proper component spacing for easy maintenance
- Status LED positioning for clear visibility
- Sturdy mounting for servo motor gate mechanism

## License

This project is open-source and available for educational and non-commercial use.

## Contributing

Feel free to submit improvements, bug fixes, or additional features through pull requests.

## Acknowledgments

- Arduino community for extensive documentation
- MFRC522 library contributors
- Open-source hardware community
