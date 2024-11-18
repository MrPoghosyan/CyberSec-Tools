import sqlite3
import hashlib
from flask import Flask, request

app = Flask(__name__)
db_name = 'test.db'

@app.route('/')
def index():
    return 'Welcome to version 2 - Hashed Passwords! <br>'

# Signup endpoint
@app.route('/signup/v2', methods=['POST'])
def signup_v2():
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS USER_HASH
              (username TEXT PRIMARY KEY NOT NULL,
              hash TEXT NOT NULL);''')
    conn.commit()
    try:
        hash_value = hashlib.sha256(request.form['password'].encode()).hexdigest()
        c.execute('INSERT INTO USER_HASH (username, hash) VALUES (?, ?)', 
                  (request.form['username'], hash_value))
        conn.commit()
    except sqlite3.IntegrityError:
        return 'Username has been registered!'
    return 'Signup success!'

# Login endpoint
def verify_hash(username, password):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    query = 'SELECT hash FROM USER_HASH WHERE username = ?'
    c.execute(query, (username,))
    records = c.fetchone()
    conn.close()
    if not records:
        return False
    return records[0] == hashlib.sha256(password.encode()).hexdigest()

@app.route('/login/v2', methods=['POST'])
def login_v2():
    if verify_hash(request.form['username'], request.form['password']):
        return 'Login success!'
    return 'Invalid username/password!'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, ssl_context='adhoc')

