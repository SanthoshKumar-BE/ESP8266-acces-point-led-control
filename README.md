# ESP8266 Three LED Web Control

This project uses an **ESP8266** (NodeMCU / Wemos D1 Mini) to create a Wi-Fi **Access Point** and host a web server that allows you to **control three LEDs** individually from any device with a web browser.  
The web interface is styled with **HTML + CSS** for a modern and responsive look.

---

## Features
- **Access Point Mode** — No external Wi-Fi needed.
- **Three independent LED controls** (ON/OFF).
- **Live LED status display** on the web page.
- **Responsive & elegant UI** for mobile and desktop.
- Simple, lightweight code — no external libraries beyond ESP8266 core.

---

## Hardware Requirements
- ESP8266 board (NodeMCU, Wemos D1 Mini, etc.)
- 3 × LEDs
- 3 × Current limiting resistors (220Ω recommended)
- Breadboard & jumper wires

---

## Pin Configuration
| LED  | ESP8266 Pin |
|------|-------------|
| LED1 | GPIO2 (D4)  |
| LED2 | GPIO4 (D2)  |
| LED3 | GPIO5 (D0)  |

You can change these pins in the code to match your wiring.

---

## How It Works
1. ESP8266 starts in **Access Point mode** with SSID and password defined in the code.
2. Connect your phone or laptop to this Wi-Fi network.
3. Open the IP address `192.168.1.1` in your browser.
4. Control each LED individually with ON/OFF buttons.

---

## Installation
1. Install **Arduino IDE** with the ESP8266 board support.
2. Clone this repository:
   ```bash
   git clone https://github.com/your-username/ESP8266-Three-LED-Web-Control.git
