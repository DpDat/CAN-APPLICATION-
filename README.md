# CAN-APPLICATION-
This application is developed using Object-Oriented Programming in C++, and it is a Qt-based product that enables users to interact with the CAN (Controller Area Network) data in vehicles.
# SCREENSHOT 
Main Screen: 
![image alt](https://github.com/DpDat/CAN-APPLICATION-/blob/fa43b92d436ccf41f4cee493f339a01802a67ee6/QT_based%20Application/MainScreen.png)
Menu Interface:
![image alt](https://github.com/DpDat/CAN-APPLICATION-/blob/b23ecbcfa824c2f941e86f6554635f908b8a6ced/QT_based%20Application/MenuScreen.png)
Implementing Monitor (Retrieve CAN đata) function with Mazda CX5 Vehicle: 
![image alt](https://github.com/DpDat/CAN-APPLICATION-/blob/d7e7e49adeaf5ddec111fc502c027ac9df09e452/QT_based%20Application/MonitorFunction.jpg)
Implementing Decode (convert some raw data into physical values) function with Mazda CX5 Vehicle: 
![image alt](https://github.com/DpDat/CAN-APPLICATION-/blob/d7e7e49adeaf5ddec111fc502c027ac9df09e452/QT_based%20Application/DecodeFunction.jpg)
Implementing OBD2 Request (Sending single frames base on standard OBD2 protocol to request specific information) function with Mazda CX5 Vehicle: 
![image alt](https://github.com/DpDat/CAN-APPLICATION-/blob/d7e7e49adeaf5ddec111fc502c027ac9df09e452/QT_based%20Application/OBD2_Request_Function.jpg)

# Necessary software tool to run the code for project
All the necessary software tools are listed in the 'Software Tools' folder. Below are images illustrating how to use the software in the project: 
![image alt](https://github.com/DpDat/CAN-APPLICATION-/blob/9a851d4b6a66133c7d4ebc05d341faea59e56183/Software%20Tools/folders%20in%20QT%20creator%20tool%20.jpg)
![image alt](https://github.com/DpDat/CAN-APPLICATION-/blob/c326b7bb7fe173f164b3db9c99179840d7297c3d/Software%20Tools/S32K144%20Configurration.png)\
# How to install software tools on the Debian operating system for Raspberry Pi 4 Model B
For QT creator:

Step 1: Update the System
1. Open a terminal on your Raspberry Pi.
2. Run the following commands to update the package list and upgrade the system:
```bash
sudo apt update
sudo apt upgrade -y
```
Step 2: Install Required Dependencies
Ensure you have all necessary dependencies for Qt Creator:
```bash
sudo apt install build-essential libgl1-mesa-dev -y
```
Step 3: Install Qt Creator Using APT
Install Qt Creator directly from the default Debian repositories:
```bash
sudo apt install qtcreator -y
```
Step 4: Verify Installation
1. After installation, verify by checking the version:
```bash
qtcreator --version
```
2. Launch Qt Creator by typing:
```bash
qtcreator
```
For S32 Design Studio: 

Step 1: Download the Installer
1. Visit the official NXP S32 Design Studio website and create an account if you don’t already have one.
2. Navigate to the downloads section and download the Linux installer for S32 Design Studio.

Step 2: Move the Installer to Your Debian Machine
If you downloaded the installer on another machine, transfer it to your Debian system using a USB drive or a file transfer tool like scp.

Step 3: Make the Installer Executable
Open a terminal and navigate to the directory containing the downloaded installer. Run the following command to make the installer executable:
```bash
chmod +x <installer-file-name>.sh
```
Replace <installer-file-name> with the actual name of the downloaded file.

Step 4: Run the Installer
Run the installer script using the following command:
```bash
sudo ./<installer-file-name>.sh
```
Follow the on-screen instructions to complete the installation.

Step 5: Install Required Dependencies
Install any missing libraries that S32 Design Studio may require. Common dependencies include libgtk2.0 and libusb-1.0. Run:
```bash
sudo apt install libgtk2.0-0 libusb-1.0-0 -y
```

Step 6: Launch S32 Design Studio
To start the S32 Design Studio IDE, navigate to the installation directory (e.g., /opt/nxp/S32DS.3.4) and run:
```bash
./s32ds
```
For PulseView Sigrok:

Step 1: Update the System
1. Open a terminal on your Raspberry Pi.
2. Run the following commands to update the package list and upgrade the system:
```bash
sudo apt update
sudo apt upgrade -y
```

Step 2: Install PulseView Using APT
Once the apt database is updated, you can install PulseView using apt-get by executing the following command:
```bash
sudo apt-get -y install pulseview
```

Step 3: Connect Your Logic Analyzer
1. Plug in your logic analyzer.
2. Open PulseView:
```bash
pulseview
```
3. Select your device and start capturing signals.

# Similarly, all the hardware tools for the project are listed in the 'Hardware' folder, and the connections for the devices are illustrated in the 'Wiring Diagram' file.

# The demo video with the application 
Please download file to watch [Demo Video](https://github.com/DpDat/CAN-APPLICATION-/blob/55fc327ce3950081a9155835f016b4064b5ead0b/DemoVideo.mp4)
