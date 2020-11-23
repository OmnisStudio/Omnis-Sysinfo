//
//  xsysinfo.cpp
//  sysinfo
//
//  Created by Andrei Augustin on 20/05/2019.
//  Copyright © 2019 Omnis Software Ltd. All rights reserved.
//

#include <extcomp.he>
#include <extfval.he>
#include <hwnd.he>

#include "sysinfo.he"
#include "xsysinfo.he"

kern_return_t macAddressInteractor::FindEthernetInterfaces(io_iterator_t *matchingServices)
{
	kern_return_t           kernResult;
	CFMutableDictionaryRef    matchingDict;
	CFMutableDictionaryRef    propertyMatchDict;
	
	matchingDict = IOServiceMatching(kIOEthernetInterfaceClass);
	
	if (NULL == matchingDict)
	{
		// error IOServiceMatching returned a NULL dictionary.
	}
	else {
		propertyMatchDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0,
																									&kCFTypeDictionaryKeyCallBacks,
																									&kCFTypeDictionaryValueCallBacks);
		
		if (NULL == propertyMatchDict)
		{
			//error CFDictionaryCreateMutable returned a NULL dictionary.
		}
		else
		{
			CFDictionarySetValue(propertyMatchDict, CFSTR(kIOPrimaryInterface), kCFBooleanTrue);
			
			CFDictionarySetValue(matchingDict, CFSTR(kIOPropertyMatchKey), propertyMatchDict);
			CFRelease(propertyMatchDict);
		}
	}
	
	kernResult = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, matchingServices);
	if (KERN_SUCCESS != kernResult)
	{
		//error printf("IOServiceGetMatchingServices returned 0x%08x\n", kernResult);
	}
	
	return kernResult;
}

kern_return_t macAddressInteractor::GetMACAddress(io_iterator_t intfIterator, UInt8 *MACAddress, UInt8 bufferSize)
{
	io_object_t        intfService;
	io_object_t        controllerService;
	kern_return_t    kernResult = KERN_FAILURE;
	
	if (bufferSize < kIOEthernetAddressSize)
	{
		return kernResult;
	}
	
	bzero(MACAddress, bufferSize);
	
	while ((intfService = IOIteratorNext(intfIterator)))
	{
		CFTypeRef    MACAddressAsCFData;
		
		kernResult = IORegistryEntryGetParentEntry(intfService,
																							 kIOServicePlane,
																							 &controllerService);
		
		if (KERN_SUCCESS != kernResult)
		{
			//error printf("IORegistryEntryGetParentEntry returned 0x%08x\n", kernResult);
		}
		else
		{
			MACAddressAsCFData = IORegistryEntryCreateCFProperty(controllerService,
																													 CFSTR(kIOMACAddress),
																													 kCFAllocatorDefault,
																													 0);
			if (MACAddressAsCFData)
			{
				CFShow(MACAddressAsCFData);
				
				CFDataGetBytes((CFDataRef)MACAddressAsCFData, CFRangeMake(0, kIOEthernetAddressSize), MACAddress);
				CFRelease(MACAddressAsCFData);
			}
			
			(void) IOObjectRelease(controllerService);
		}
		
		(void) IOObjectRelease(intfService);
	}
	
	return kernResult;
}

void macAddressInteractor::getMacAddress(char (&macAddress)[18]) {
	kern_return_t    kernResult = KERN_SUCCESS;
	io_iterator_t    intfIterator;
	UInt8            MACAddress[kIOEthernetAddressSize];
	
	kernResult = macAddressInteractor::FindEthernetInterfaces(&intfIterator);
	
	if (KERN_SUCCESS != kernResult)
	{
		//error FindEthernetInterfaces failed
	}
	else
	{
		kernResult = macAddressInteractor::GetMACAddress(intfIterator, MACAddress, sizeof(MACAddress));
		
		if (KERN_SUCCESS != kernResult)
		{
			//error GetMACAddress failed
		}
		else {
			sprintf(
							macAddress,
							"%02X-%02X-%02X-%02X-%02X-%02X",
							MACAddress[0],
							MACAddress[1],
							MACAddress[2],
							MACAddress[3],
							MACAddress[4],
							MACAddress[5]);
		}
		
		(void) IOObjectRelease(intfIterator);    // Release the iterator
	}
}

qbool sys_info::getMacAddress(EXTfldval &returnValue)
{
	char myMac[18]; // [13] to [17] is equal to '\0'
	macAddressInteractor::getMacAddress(myMac);
	if (myMac[16] != '\0') // If array has emtpy [16] element, getMacAddress failed
	{
		returnValue.setchar(myMac);
		return qtrue;
	}
	else
		return qfalse;
}

qbool sys_info::getComputerName(EXTfldval &returnValue)
{
	size_t len = 255;
	char* computerName = (char*)malloc(len+1);
	memset(computerName, 0, len + 1);
	gethostname(computerName, len);
	
	if (computerName)
	{
		returnValue.setchar(computerName);
		free(computerName);
		return qtrue;
	}
	else
	{
		free(computerName);
		return qfalse;
	}
}

qbool sys_info::getModel(EXTfldval &returnValue)
{
	size_t len = 0;
	sysctlbyname("hw.model", NULL, &len, NULL, 0);
	
	char* model = (char*)malloc(len + 1);
	memset(model, 0, len + 1);
	
	sysctlbyname("hw.model", model, &len, NULL, 0);
	
	if (model)
	{
		returnValue.setchar(model);
		free(model);
		return qtrue;
	}
	else
	{
		free(model);
		return qfalse;
	}
}

qbool sys_info::getManufacturer(EXTfldval &returnValue)
{
	returnValue.setchar("Apple");
	return qtrue;
}

qbool sys_info::getUsername(EXTfldval &returnValue)
{
	char* username;
	username = getenv("USER");
	if (username)
	{
		returnValue.setchar(username);
		return qtrue;
	}
	else
		return qfalse;
}

qbool sys_info::getScreenCount(EXTfldval &returnValue)
{
	int screenCount = (int) NSScreen.screens.count;
	if (screenCount>=1)
	{
		returnValue.setLong64((qlong64)screenCount);
		return qtrue;
	}
	else
		return qfalse;
	
}

qbool sys_info::getColourDepth(EXTfldval &returnValue)
{
	const NSWindowDepth *wndDepth = NSAvailableWindowDepths();
	int bitsPerPixel = (int) NSBitsPerPixelFromDepth(*wndDepth);
	if (bitsPerPixel>0)
	{
		returnValue.setLong64((qlong64)bitsPerPixel);
		return qtrue;
	}
	else
		return qfalse;
}

qbool sys_info::getScalingFactor(EXTfldval &returnValue)
{
	float scalingFactor = (float) [[NSScreen mainScreen] backingScaleFactor];
	if (scalingFactor>0)
	{
		returnValue.setNum(scalingFactor);
		return qtrue;
	}
	else
		return qfalse;
}


