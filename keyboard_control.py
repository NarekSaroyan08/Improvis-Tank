# # keyboard.serial
# from pynput import keyboard
# import serial

# Tank = serial.Serial("/dev/ttyACM0", 9600)

# # while True :
# #     if keyboard.is_press('a') :
          
# #        Tank.write(b'W')
    
# #     elif keyboard.is_pressed('d') :
        
# #         Tank.write(b'D')
# #     elif keyboard.is_pressed('w') :

# #         Tank.write(b'W')
# #     elif keyboard.is_pressed('s') :
        
# #         Tank.write(b'S')

# #     else :
# #         Tank.write(b'X')
# # flag = False
# def on_press(key):
#     try:
#         # print(f'Key {key.char} pressed')
#         # print(f'key type {type(key.char)}]
#         if key.char == "f" :
#             clear = input("please pressed random key so that everything is cleared")
#             X = input("input X cordinate - ")
#             print(X)
#             # Tank.write(int(X))
#             Y = input("input Y cordinate - ")
#             print(Y)
#             # Tank.write(int(Y))
#             Z = input("input Yes or No (1 or 0) - ")
#             print(Z)
#             # Tank.write(int(Z))
#             # return
#             key.char = "x"

#             with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
#                 listener.join()
#         if key.char == "a" :
#             Tank.write(b'A')
#             # flag = True
#         elif key.char == "d" :

#             Tank.write(b'D')
#             # flag = True
#         elif key.char == "w" :
#             # flag = True
#             Tank.write(b'W')
#         elif key.char == "s" :
#             # print("S write Arduino")
#             Tank.write(b'S')
#             # flag = True
#         else :
#             Tank.write(b'X')
        
#         Tank.write(b'X')
    
#     except AttributeError:
#         print(f'Special key {key} pressed')


# def on_release(key):

#     # print(f'Key {key} released')
#     print(f'key type {type(key)} ')
#     if key.char == "f" :
#         clear = input("please pressed random key so that everything is cleared")
#         X = input("input X cordinate - ")
#         print(X)
#         # Tank.write(int(X))
#         Y = input("input Y cordinate - ")
#         print(Y)
#         # Tank.write(int(Y))
#         Z = input("input Yes or No (1 or 0) - ")
#         print(Z)
#         # Tank.write(int(Z))
#         # return 0
#         key.char = "x"
#         with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
#             listener.join()

#     if key.char == "a" :
#             Tank.write(b'A')
#             # flag = True
#     elif key.char == "d" :

#         Tank.write(b'D')
#         # flag = True
#     elif key.char == "w" :
#         # flag = True
#         Tank.write(b'W')
#     elif key.char == "s" :
#         # print("S write Arduino")
#         Tank.write(b'S')
#         # flag = True
#     else :
#         Tank.write(b'X')
    
#     # Tank.write(b'X')

# with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
#     listener.join()




from pynput import keyboard
import serial
import struct

Tank = serial.Serial("/dev/ttyACM0", 9600)

def send_coordinates():
    X = int(input("Input X coordinate - "))
    Tank.write(X)
    Y = int(input("Input Y coordinate - "))
    Tank.write(Y)
    Z = int(input("Input Yes or No (1 or 0) - "))
    Tank.write(Z)
    data = struct.pack('!iii', X, Y, Z)

def on_press(key):
    try:
        if hasattr(key, 'char'):
            if key.char == "f":
                clear = input("Please press a random key to clear")
                send_coordinates()

            elif key.char in ["a", "d", "w", "s"]:
                Tank.write(key.char.encode())

            else:
                Tank.write(b'X')

    except AttributeError:
        print(f'Special key {key} pressed')

def on_release(key):
    if hasattr(key, 'char') and key.char == "f":
        # You can handle any additional logic for the 'f' key release here
        pass

    elif hasattr(key, 'char') and key.char in ["a", "d", "w", "s"]:
        Tank.write(b'X')  # Release X here if needed

    else:
        Tank.write(b'X')

with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
