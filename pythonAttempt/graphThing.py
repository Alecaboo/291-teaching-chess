import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.animation as animation

# Set up the serial connection
arduino_port = '/dev/cu.usbmodem21201'  # Set this to whatever port the Arduino thinks it's connected to
baud_rate = 9600 # Same baud you set with Serial.begin in arduino (I just like 9600)
ser = serial.Serial(arduino_port, baud_rate)

# Grid dimensions
grid_size = 8
square_size = 1

# Create a figure and axes
fig, ax = plt.subplots()

# Initialize an empty grid of rectangles
rects = []
for i in range(grid_size):
    row = []
    for j in range(grid_size):
        # Create rectangles with no fill initially
        rect = patches.Rectangle(
            (j, grid_size - i - 1),  # Rectangle placement
            square_size,  # Width
            square_size,  # Height
            linewidth=1,
            edgecolor='black',
            facecolor='none',  # Initially empty
        )
        ax.add_patch(rect)
        row.append(rect)
    rects.append(row)

# Set the axis limits and aspect ratio
ax.set_xlim(0, grid_size)
ax.set_ylim(0, grid_size)
ax.set_aspect('equal')


def read_array_from_serial():
    """Read a 2D array from the serial port."""
    array = []
    while True: #this is, frankly, some mild shenanigans that I both stole from other people and slapped together with chatGPT.
        try:
            line = ser.readline().decode('utf-8').strip()
            if line == "---":  # Break on separator
                break
            array.append([x.strip() for x in line.split(',')])  
        except ValueError:
            continue
    return np.array(array)

def update(frame):
    """Update the grid colors based on new data."""
    data = read_array_from_serial()
    print(data)
    for i in range(grid_size):
        for j in range(grid_size):
            # Map char inputs to colors
            char = data[i][j]

            if char == 'R' or char == '1':
                rects[i][j].set_facecolor('red')  
            elif char == 'G' or char == '0' or char == '48':
                rects[i][j].set_facecolor('green') 
            elif char == 'B':
                rects[i][j].set_facecolor('blue') 
            elif char == 'N':
                rects[i][j].set_facecolor('none')  # No color
            elif char == 'P':
                rects[i][j].set_facecolor('pink') 
            else:
                rects[i][j].set_facecolor('yellow')

# Create the animation
ani = animation.FuncAnimation(fig, update, interval=500)

# Show the plot
print("Hey, here's a sample array, just so you know what it looks like")
print(read_array_from_serial())
plt.show()
