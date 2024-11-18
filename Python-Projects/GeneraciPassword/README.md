# Password Management

## Overview
This project demonstrates the evolution of password storage and management:
1. **Version V1:** Storing passwords in plain text (insecure).
2. **Version V2:** Storing hashed passwords using SHA-256 for better security.

## Features
- **V1:** Simple signup and login with plain text password storage.
- **V2:** Improved signup and login with password hashing.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-repository.git

## Install dependencies:
    pip install flask

### Usage:
```bash
    1. Start the server for the desired version:
    Version 1:
        python3 app_v1.py

    Version 2:
        python3 app_v2.py

    2. Test the endpoints using curl:
    Version 1:
        curl -k -X POST -F 'username=Nika' -F 'password=NikaPassword1' 'https://0.0.0.0:5000/signup/v1'
        curl -k -X POST -F 'username=Nika' -F 'password=NikaPassword1' 'https://0.0.0.0:5000/login/v1'

    Version 2:
        curl -k -X POST -F 'username=Nika' -F 'password=NikaPassword1' 'https://0.0.0.0:5000/signup/v2'
        curl -k -X POST -F 'username=Nika' -F 'password=NikaPassword1' 'https://0.0.0.0:5000/login/v2'


Notes:

    Use sqlitebrowser to view the database contents for verification.
    This is a basic project to demonstrate password management, it should not be used in production without additional security measures.
