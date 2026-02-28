import serial

PORT = '/dev/ttyACM0'
BAUD = 57600

ser = serial.Serial(
    port=PORT,
    baudrate=BAUD,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

ser.isOpen()
print(f"Serial port opened on {PORT} at baudrate {BAUD}")

try:
    while True:
        while ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            print(f"Received: {line}")
        
        time.sleep(1)
except KeyboardInterrupt:
    print("Exiting...")
except Exception as e:
    print(e)
finally:
    ser.close()
