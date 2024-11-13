# Network Scanner

## Project Overview
Network Scanner is a simple C++ program designed to identify active devices within a specific IP range and scan each active device for open ports. This tool can be used in local networks for quick diagnostics, security analysis, and network exploration.

## Features
- **Ping Sweep**: Scans a specified IP range (e.g., `192.168.1.1` to `192.168.1.254`) to detect active devices.
- **Port Scanning**: For each active IP, it scans ports (1–1024) to identify open ports, indicating active services.

## Project Structure
Network-Scanner/ 
├── include/ 
│ └── network_scanner.h      # Header file containing function declarations 
├── src/ 
│ ├── network_scanner.cpp    # Core functionality of the scanner 
│ └── main.cpp               # Entry point of the program 
└──README.md                 # Project documentation 

## Navigate to the project directory:
  bash:
  cd Network-Scanner
  g++ -o network_scanner src/main.cpp src/network_scanner.cpp -I include
  ./network_scanner

Note: The program is designed for Unix-based systems (Linux or macOS). Administrator/root permissions may be required to access certain network functions.


How It Works

    Ping Sweep: The program sends a simple ping command to each IP in the specified range to check if it responds.
    Port Scanning: For each active IP, it attempts to connect to each port (1–1024) to determine if the port is open.

Requirements

    C++11 or later: Required for the standard C++ libraries used.
    Unix-based OS: For socket and network functions.
    Root/Administrator Privileges: Optional, may be needed for network access.
