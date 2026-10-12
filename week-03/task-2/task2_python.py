import os

# 1. Fix Tcl/Tk environment paths
os.environ['TCL_LIBRARY'] = r'C:\Program Files\Python313\tcl\tcl8.6'
os.environ['TK_LIBRARY'] = r'C:\Program Files\Python313\tcl\tk8.6'

# 2. Force Matplotlib backend BEFORE importing pyplot
import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt
import serial

# 3. Open the serial port FIRST (Make sure Arduino IDE Serial Monitor is closed!)
ser = serial.Serial('COM5', 9600)

# 4. Set up interactive plotting
plt.ion()
fig, ax = plt.subplots()
x_vals, y_vals = [], []

(line_plot,) = ax.plot([], [], color='b', linewidth=2)

ax.set_title("Real-Time Potentiometer Readings")
ax.set_xlabel("Sample Count")
ax.set_ylabel("Potentiometer Value")

try:
    print("Plotting potentiometer values in real-time... Press Ctrl+C to stop.")
    count = 0
    MAX_POINTS = 150  # Keeps the graph fast by only showing the latest points

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            if line.isdigit():
                pot_value = int(line)
                print("Potentiometer Value:", pot_value)

                x_vals.append(count)
                y_vals.append(pot_value)
                count += 1

                # Trim arrays to keep only the most recent points (prevents lagging)
                if len(x_vals) > MAX_POINTS:
                    x_vals.pop(0)
                    y_vals.pop(0)

                line_plot.set_xdata(x_vals)
                line_plot.set_ydata(y_vals)

                ax.relim()
                ax.autoscale_view()
                ax.set_xlim(max(0, count - MAX_POINTS), count + 5)

                fig.canvas.draw()
                fig.canvas.flush_events()
        else:
            plt.pause(0.001)

except KeyboardInterrupt:
    ser.write(b'q')
    ser.close()
    plt.ioff()
    plt.show()
    print("Serial connection closed.")
