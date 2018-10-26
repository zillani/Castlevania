#include "Keyboard.h"
#include "../Utilities/FileLogger.h"

Input_ Keyboard::input;
InputDevice_ Keyboard::inputDevice;

void Keyboard::Initialize(HWND hWnd)
{
	auto result = DirectInput8Create(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&input, nullptr);

	if (result != DI_OK)
	{
		FileLogger::GetInstance().Error("DirectInput8Create failed!");
		return;
	}

	result = input->CreateDevice(GUID_SysKeyboard, &inputDevice, nullptr);

	// TO-DO: put in exception handling
	if (result != DI_OK)
	{
		FileLogger::GetInstance().Error("CreateDevice failed!");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	result = inputDevice->SetDataFormat(&c_dfDIKeyboard);

	result = inputDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	auto dipdw = DIPROPDWORD{};

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	result = inputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	result = inputDevice->Acquire();
	if (result != DI_OK)
	{
		FileLogger::GetInstance().Error("DINPUT8::Acquire failed!");
		return;
	}

	FileLogger::GetInstance().Info("Keyboard has been initialized successfully");
}

KeyboardState Keyboard::GetState()
{
	unsigned char keyStates[KEYSTATE_BUFFER_SIZE]; // DirectInput keyboard state buffer 

	// Collect all key states first
	auto result = inputDevice->GetDeviceState(sizeof(keyStates), keyStates);

	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			// TODO: error here (potentially)
			result = inputDevice->Acquire();

			if (result == DI_OK)
				FileLogger::GetInstance().Info("Keyboard re-acquired!");
			else
				return KeyboardState(nullptr);
		}
		else
		{
			return KeyboardState(nullptr);
			// FileLogger::GetInstance().Error("DINPUT::GetDeviceState failed. Error: " + std::to_string(hr));
		}
	}

	return KeyboardState(keyStates);
}

void Keyboard::Release()
{
	if (inputDevice != nullptr)
	{
		inputDevice->Unacquire();
		inputDevice->Release();
		inputDevice = nullptr;
	}
}