import serial
import time

# Set the correct serial port and baud rate
ser = serial.Serial('/dev/ttyACM0', 9600)

def send_coordinates(x, y):
    # Send X coordinate
    ser.write(x)
    time.sleep(0.1)  # delay to allow Arduino to process the data

    # Send Y coordinate
    ser.write(y)
    time.sleep(0.1)  # delay to allow Arduino to process the data

if __name__ == "__main__":
    try:
        while True:
            x_coord = int(input("Enter X coordinate: "))
            y_coord = int(input("Enter Y coordinate: "))

            send_coordinates(x_coord, y_coord)

            ready_to_rotate_z = input("Ready to rotate Z? Enter '1' if yes: ")
            if ready_to_rotate_z == '1':
                ser.write(1)  # Send a signal to rotate Z in Arduino
                time.sleep(0.1)  # delay to allow Arduino to process the data

    except KeyboardInterrupt:
        print("\nExiting the program.")
    finally:
        ser.close()  # Close the serial port
