# Sumo
A wireless sumo robot system built with **ESP8266 NodeMCU V3**, the robot creates its own WIFI access point and serves web-based joystick controller that can be accessed from any device. Communication between the web interface and the robot is handled in real-time using WebSocket for low-latency control.

## Hardware Requirements
### ESP8266 Development Board
- NodeMCU V3
### Motor Driver & Motors
- Dual H-Bridge Motor Driver (e.g., L298N)
- 2x DC Motors (differential drive)
- External power supply (6–12V for motors)
### Wiring Configuration
| ESP8266 Pin | Motor Driver         |
|-------------|----------------------|
| D1          | Right Motor Forward  |
| D2          | Right Motor Backward |
| D3          | Left Motor Forward   |
| D4          | Left Motor Backward  |

Defined in `include/config.h`.
## Software Requirements
- [PlatformIO](https://platformio.org)
- [Node.js](https://nodejs.org)
- [Node Package Manager (NPM)](npmjs.com) or pnpm (recommended)
- [Python](https://python.org)
## Upload Instructions
### 1. Make sure you've installed all the required software.
### 2. Clone this repo
```
git clone https://github.com/Siotics/Sumo
cd Sumo
```
### 3. Install Web Dependencies 
```
cd web
npm install
```
### 4. Build the Web App
```
npm run build
```
### 5. Build & Flash the firmware
```
cd ..
pio run -t upload
```
## Usage
### 1. Power on the boot
After uploading firmware and filesystem, power on your ESP8266
### 2. Connect to the WIFI AP
- Look for a WIFI network named `SUMO-XXXXXXXX` (where X's are the chip ID)
- Default Password is `12345678`
### 3. Open the Controller
- Open a web browser and go to any website (you'll be redirected)
- Or directly navigate to 192.168.4.1
### 4. Control the robot
- **Touch/Mouse**: Use the central joystick for analog control
- **Keyboard**: Use WASD or arrow keys for digital control
- **Touch Buttons**: Use the directional buttons around the joystick

## Project Structures
```
├── include/
│   ├── config.h              # Pin definitions and WiFi settings
│   └── README
├── lib/
│   ├── DNS/                  # Captive portal DNS server
│   ├── WebServer/            # HTTP and WebSocket server
│   ├── WheelController/      # Motor control logic
│   └── WifiAP/              # WiFi access point setup
├── src/
│   └── main.cpp             # Main application entry point
├── web/                     # Web interface (SvelteKit)
│   ├── src/
│   │   ├── lib/
│   │   │   ├── components/  # Svelte components
│   │   │   └── stores/      # WebSocket and state management
│   │   └── routes/          # SvelteKit pages
│   ├── package.json
│   └── vite.config.ts
├── extra_scripts.py         # PlatformIO build automation
└── platformio.ini          # PlatformIO configuration
```
## Configuration
See `include/config.h`