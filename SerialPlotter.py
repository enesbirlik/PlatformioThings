import serial
import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

# i want to make a realtim plotter for the data from the arduino arduino publishing servo motor angle between 0 180 and i vant to see it in real time. angle/time
# serail port sending integer values between 0 and 180 can i see it in real time?

# initialize serial port
ser = serial.Serial('/dev/ttyACM0', 9600)

print("connected to: " + ser.portstr)

# value = ser.readline()
# value = int(value)
# print(value)

# i want to show 0, 90 , 180 dergree in the y axis and line will start at the 0 time and it will go on to 20 seconds

plt.rcParams['axes.facecolor'] = '#e6e6fa'
plt.rcParams['axes.edgecolor'] = '#89929b'
plt.rcParams['axes.labelcolor'] = '#ffffff'
plt.rcParams['xtick.color'] = '#ecf2f8'
plt.rcParams['figure.facecolor'] = '#015697'
plt.rcParams['ytick.color'] = '#ecf2f8'
plt.rcParams['lines.linewidth'] = 4

class AnimationPlot:

    def animate(self, i, dataList, datalist2, ser):
        # read serial port
        global dataList2
        value = ser.readline()
        value = value.decode().strip()
        valueSplit = value.split(",")
        #value = int(value)
        val = int(valueSplit[0])
        val2 = int(valueSplit[1])
        #print(value)

        try:
            dataList.append(val)
            dataList2.append(val2)
        except:
            pass

        dataList = dataList[-1000:]
        dataList2 = dataList2[-1000:]

        ax.clear()
        
        self.getPlotFormat()
        ax.plot(dataList, color='#eb174a')
        ax.plot(dataList2, color='g')
    
    def getPlotFormat(self):
        ax.set_ylim(0, 180)
        ax.set_xlim(0, 1000)
        ax.set_title('Servo Angle vs Time',fontdict={'fontsize': 24, 'fontweight': 'medium'})
        ax.set_ylabel('Angle (deg)')
        ax.set_xlabel('Time (ms)')
        ax.grid(True)
        ax.set_yticks([0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180])



dataList = []
dataList2 = []

fig=plt.figure()
ax=fig.add_subplot(1,1,1)

realTimePlot = AnimationPlot()

ani = FuncAnimation(fig, realTimePlot.animate, frames=100, fargs=(dataList, dataList2, ser), interval=10)

plt.show()
ser.close()