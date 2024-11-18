# Password Management

## Version V1
- Passwords are stored in plain text.
- Contains endpoints for:
  - User signup (`/signup/v1`)
  - User login (`/login/v1`)

### Usage:
```bash
python3 app_v1.py

## Test the endpoints using curl:
    curl -k -X POST -F 'username=Nika' -F 'password=NikaPassword1' 'https://0.0.0.0:5000/signup/v1'
    curl -k -X POST -F 'username=Nika' -F 'password=NikaPassword1' 'https://0.0.0.0:5000/login/v1'

Notes:

    Use sqlitebrowser to view the database contents for verification.
    This is a basic project to demonstrate password management, it should not be used in production without additional security measures.
