device_path = "/dev/myCharDevice" # path to device
limit = 200 # maximum buffer size (myCharDevice is 200 bytes)

with open(device_path, "w+") as f: # opens device for read & write
    while True:
        print("Type r to read from device")
        print("Type w to write to device")
        print("Type any other key to exit")
        char = input("Enter command:")
        if char == 'w':
            print("Input must be no greater than",limit)
            write_buffer = input("enter data: ")
            write_buffer = write_buffer[:limit] # Forces a device limit
            f.write(write_buffer) # writes to device
        elif char == 'r':
            read_buffer = f.read() # limit maybe imposed later
            print("Device contents:")
            print(read_buffer)
        else:
            break