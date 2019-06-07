# Requirements

Omnis Studio **10** or later. Source should be compiled with the SDK 8 if needed.

## Contents

##### xcomp

This folder contains the compiled xcomp that you can add to Omnis.

##### sysinfo_linux.tar.gz

This zip file contains the sources and SDK 10 and a buildSysinfo.sh script which once executed, will compile the xcomp and make it available in the releaseuni and releasuni-headless folders.

##### sysinfo_mac.zip

This zip file contains the sources and SDK 10. Use sysinfo.xcodeproj in order to compile the source.

##### sysinfo_windows.zip

This zip file contains the sources but the Windows SDK 10 is too big to upload onto GitHub. Placing complib and ulibs folders at the same levels as the sysinfo folder shoould allow you to compile via the sysinfo.sln.

# Usage

In order to use this xcomp, you can use one of its functions described below, in the format **Do sysinfo.$functionName(cError) Returns cReturnedValue**

$getmacaddr(cError) : returns the mac address of the device.
$getmanufacturer(cError) : returns the manufacturer of the device.
$getmodel(cError) : returns the model of the device.
$getname(cError) : returns the name of the device, this is the hostname.
$getusername(cError) : returns the username of the user from the machine.

# To do

Add more features over time!
