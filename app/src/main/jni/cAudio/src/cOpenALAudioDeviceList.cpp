// Copyright (c) 2008-2011 Raynaldo (Wildicv) Rivera, Joshua (Dark_Kilauea) Jones, Murat (wolfmanfx) Sari
// This file is part of the "cAudio Engine"
// For conditions of distribution and use, see copyright notice in cAudio.h

#pragma once

#include "cOpenALAudioDeviceList.h"
#include <al.h>
#include <alc.h>
#include <alext.h>

namespace cAudio
{
	cOpenALAudioDeviceList::cOpenALAudioDeviceList(IDeviceType deviceType)
	{
		DeviceType = deviceType;
		ALCenum specifier = 0;
		ALCenum defaultDevice = 0;

		if(DeviceType == DT_RECORDING)
		{
			specifier = ALC_CAPTURE_DEVICE_SPECIFIER;
			defaultDevice = ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER;
		}
		else
		{
			if( alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT") == AL_TRUE )
			{
				specifier = ALC_ALL_DEVICES_SPECIFIER;
				defaultDevice = ALC_DEFAULT_ALL_DEVICES_SPECIFIER;
			}
			else if( alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == AL_TRUE )
			{	
				specifier = ALC_DEVICE_SPECIFIER;
				defaultDevice = ALC_DEFAULT_DEVICE_SPECIFIER;
			}
		}
		
		if (specifier != 0 && defaultDevice != 0)
		{
			const char* deviceList = alcGetString(NULL, specifier);
			if (deviceList)
			{
				while(*deviceList)
				{
					cAudioString device(deviceList);
					AvailableDevices.push_back(device);
					deviceList += strlen(deviceList) + 1;
				}
			}

			// Get the name of the 'default' capture device
			DefaultDevice = alcGetString(NULL, defaultDevice);
		}
	}

	cOpenALAudioDeviceList::~cOpenALAudioDeviceList() {}

	cAudioString cOpenALAudioDeviceList::getDefaultDeviceName()
	{
		return DefaultDevice;
	}

	unsigned int cOpenALAudioDeviceList::getDeviceCount()
	{
		return (unsigned int)AvailableDevices.size();
	}

	cAudioString cOpenALAudioDeviceList::getDeviceName(unsigned int idx)
	{
		if (AvailableDevices.size() > idx)
		{
			return AvailableDevices[idx];
		}
		return cAudioString("");
	}

	cAudioString cOpenALAudioDeviceList::getDeviceDescription(unsigned int idx)
	{
		return getDeviceName(idx); // In OpenAL deviceName is human readable
	}

	bool cOpenALAudioDeviceList::isSupported()
	{
		if(DeviceType == DT_RECORDING)
		{
			return alcIsExtensionPresent(NULL, "ALC_EXT_CAPTURE") == AL_TRUE && AvailableDevices.size() > 0;
		}
		return AvailableDevices.size() > 0;
	}
}
