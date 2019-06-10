# Requirements

Omnis Studio **10** or later. Source can be used to compile with previous SDKs if you want to extend support to Studio 8.1.x for example.

## Contents

##### xcomp

This folder contains the folders with the compiled xcomp that you can add to Omnis.

##### xcomp/studio81x

This folder contains the folders with the compiled xcomp that you can add to Omnis 8.1.x.

##### sysinfo_linux.tar.gz

This zip file contains the sources and SDK 10 and a buildSysinfo.sh script which once executed, will compile the xcomp and make it available in the releaseuni and releasuni-headless folders.

##### sysinfo_mac.zip

This zip file contains the sources and SDK 10. Use sysinfo.xcodeproj in order to compile the source.

##### sysinfo_windows.zip

This zip file contains the sources but the Windows SDK 10 is too big to upload onto GitHub. Placing complib and ulibs folders at the same levels as the sysinfo folder shoould allow you to compile via the sysinfo.sln.

# Usage

In order to use this xcomp, you can use one of its functions described below.

Do sysinfo.$getmacaddr(cError) Returns cReturnedValue : returns the mac address of the device.

Do sysinfo.$getmanufacturer(cError) Returns cReturnedValue : returns the manufacturer of the device.

Do sysinfo.$getmodel(cError) Returns cReturnedValue : returns the model of the device.

Do sysinfo.$getname(cError) Returns cReturnedValue : returns the name of the device, this is the hostname.

Do sysinfo.$getusername(cError) Returns cReturnedValue : returns the username of the user from the machine.

# To do

Add 8.1.x xcomp for Linux.

Add more features over time!
