//
//  sysinfo.cpp
//  sysinfo
//
//  Created by Andrei Augustin on 17/05/2019.
//  Copyright © 2019 Omnis Software Ltd. All rights reserved.
//

#include <extcomp.he>
#include <extfval.he>
#include <hwnd.he>

#include "sysinfo.he"

// SYSINFO Static Functions' Parameters
ECOparam sysinfoStaticFunctionsParameters[1] =
{
	7000, fftCharacter, 0, 0
};

// SYSINFO Static Functions
ECOmethodEvent sysinfoStaticFunctions[] =
{
	sysinfo_GetUsername, 			8000, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
	sysinfo_GetModel, 				8001, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
	sysinfo_GetManufacturer, 	8002, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
	sysinfo_GetName, 					8003, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
	sysinfo_GetMacAddress, 		8004, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
	sysinfo_GetScreenCount, 	8005, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
	sysinfo_GetColourDepth, 	8006, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
	sysinfo_GetScalingFactor, 8007, fftCharacter, 1, &sysinfoStaticFunctionsParameters[0], 0, 0,
};

#define sysinfoMethod_Count (sizeof(sysinfoStaticFunctions)/sizeof(sysinfoStaticFunctions[0]))


/*	Error handling	*/

static void setError(qlong errorCode, str80 &errorText, EXTfldval &returnedError)
{
	RESloadString(gInstLib, errorCode, errorText);
	returnedError.setChar(errorText);
}

extern "C" LRESULT OMNISWNDPROC sysinfoWndProc(HWND hwnd, LPARAM Msg, WPARAM wParam, LPARAM lParam, EXTCompInfo* eci)
{
	ECOsetupCallbacks(hwnd, eci);
	switch (Msg)
	{
		case ECM_GETCOMPLIBINFO:
		{
			return ECOreturnCompInfo(gInstLib, eci, LIB_RES_NAME, COMPONENT_COUNT);
		}
		case ECM_CONNECT:
		{
			return EXT_FLAG_LOADED | EXT_FLAG_ALWAYS_USABLE | EXT_FLAG_NVOBJECTS;
		}
		case ECM_GETSTATICOBJECT:
		{
			return ECOreturnMethods(gInstLib, eci, &sysinfoStaticFunctions[0], sysinfoMethod_Count);
		}
		case ECM_METHODCALL:
		{
			EXTfldval returnValue;
			str80 insufficientParameters;
			
			EXTParamInfo* errorParam = ECOfindParamNum(eci, 1);
			
			if (errorParam == nullptr || errorParam == NULL)
			{
				RESloadString(gInstLib,10000,insufficientParameters);
				returnValue.setChar(insufficientParameters);
				ECOaddParam(eci, &returnValue);
				return qtrue;
			}
			else
			{
				EXTfldval returnValue;
				qbool hasReturnValue = qfalse;
				EXTParamInfo* errorParam = ECOfindParamNum(eci, 1);
				EXTfldval error((qfldval)errorParam->mData);
				str80 errorText;
				
				switch (ECOgetId(eci))
				{
					case sysinfo_GetUsername:
					{
						hasReturnValue = sys_info::getUsername(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10001, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
						
					case sysinfo_GetModel:
					{
						hasReturnValue = sys_info::getModel(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10002, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
						
					case sysinfo_GetName:
					{
						hasReturnValue = sys_info::getComputerName(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10003, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
						
					case sysinfo_GetMacAddress:
					{
						hasReturnValue = sys_info::getMacAddress(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10004, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
						
					case sysinfo_GetManufacturer:
					{
						hasReturnValue = sys_info::getManufacturer(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10005, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
					
					case sysinfo_GetScreenCount:
					{
						hasReturnValue = sys_info::getScreenCount(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10006, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
						
					case sysinfo_GetColourDepth:
					{
						hasReturnValue = sys_info::getColourDepth(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10007, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
						
					case sysinfo_GetScalingFactor:
					{
						hasReturnValue = sys_info::getScalingFactor(returnValue);
						
						if (!hasReturnValue)
						{
							setError(10008, errorText, error);
							ECOsetParameterChanged(eci, 1);
						}
						break;
					}
						
				}
				// If hasReturnValue is false, zero is returned to Omnis.
				if (hasReturnValue == qtrue)
				{
					ECOaddParam(eci, &returnValue);
					return qtrue;
				}
				else
				{
					// Method not found, Omnis user gets a returned value of 0 and
					// error text in their parameter.
					return qfalse;
				}
			}
		}
	}
	return WNDdefWindowProc(hwnd, (UINT)Msg, wParam, lParam, eci);
}
