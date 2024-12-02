import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.animation as animation

# Set up the serial connection
arduino_port = '/dev/cu.usbmodem2124301'  # Update with your Arduino's port
baud_rate = 9600
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
    while True:
        try:
            line = ser.readline().decode('utf-8').strip()
            if line == "---":  # Break on separator
                break
            array.append([x.strip() for x in line.split(',')])  # Read chars instead of ints
        except ValueError:
            continue
    return np.array(array)

def update(frame):
    """Update the grid colors based on new data."""
    data = read_array_from_serial()
    for i in range(grid_size):
        for j in range(grid_size):
            # Map char inputs to colors
            char = data[i][j]

            if char == 'R':
                rects[i][j].set_facecolor('red')  # Red color
            elif char == 'G':
                rects[i][j].set_facecolor('green')  # Green color
            elif char == 'B':
                rects[i][j].set_facecolor('blue')  # Blue color
            elif char == 'N':
                rects[i][j].set_facecolor('none')  # No color
            elif char == 'P':
                rects[i][j].set_facecolor('pink') # Pink!

# Create the animation
ani = animation.FuncAnimation(fig, update, interval=500)

# Show the plot
print("Hey, here's a sample array, just so you know what it looks like")
print(read_array_from_serial())
plt.show()
