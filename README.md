# Requirements

Omnis Studio **10.1** or later. Source can be used to compile with previous SDKs if you want to extend support to Studio 8.1.x for example.

# Contents

##### xcomp

This folder contains the folders with the compiled xcomp that you can add to Omnis.

##### sysinfo_linux.tar.gz

This zip file contains the sources and SDK 10 and a buildSysinfo.sh script which once executed, will compile the xcomp and make it available in the releaseuni and releasuni-headless folders.

##### sysinfo_mac 

This folder contains the sources, you will need to add the complib inside this folder. Use sysinfo.xcodeproj project in order to compile the source.

##### sysinfo_windows.zip

This zip file contains the sources but the Windows SDK 10 is too big to upload onto GitHub. Placing complib and ulibs folders at the same levels as the sysinfo folder shoould allow you to compile via the sysinfo.sln.

# Usage

In order to use this xcomp, you can use one of its functions described below.

Do sysinfo.$getmacaddr(cError) Returns cReturnedValue : returns the mac address of the device.

Do sysinfo.$getmanufacturer(cError) Returns cReturnedValue : returns the manufacturer of the device.

Do sysinfo.$getmodel(cError) Returns cReturnedValue : returns the model of the device.

Do sysinfo.$getname(cError) Returns cReturnedValue : returns the name of the device, this is the hostname.

Do sysinfo.$getusername(cError) Returns cReturnedValue : returns the username of the user from the machine.

**macOS only - Windows will get these functions soon**

Do sysinfo.$getscalingfactor(cError) Returns iReturnedValue : returns the scaling factor of the main screen.

Do sysinfo.$getcolourdepth(cError) Returns iReturnedValue : returns the colour depth of a single channel (can be multipled by 3 if you want RGB colour depth and by 4 if you want RGB + Alpha channel).

Do sysinfo.$getscreencount(cError) Returns iReturnedValue : returns the number of screens in use identified by the OS.

# To do

Port $getscalingfactor, $getcolourdepth and $getscreencount to Windows.

Add 8.1.x xcomp for Linux.

Add more features over time!
