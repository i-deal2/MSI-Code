import serial

# Replace 'COM7' with your actual port if it changes
ser = serial.Serial('COM7', 9600)

try:
    print("Reading potentiometer... Press Ctrl+C to stop.")
    while True:
        pot_value = ser.readline().decode().strip()
        if pot_value:
            print("Potentiometer Value:", pot_value)

except KeyboardInterrupt:
    ser.close()
    print("Serial connection closed.")
