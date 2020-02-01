#include "STSLSHost.h"
#include "frc/SerialPort.h"

IndicatorLights::IndicatorLights(const wpi::Twine& device, frc::SerialPort::Port port = frc::SerialPort::Port::kUSB)
{
	// Create SerialPort instance with specified settings.
	// We will use this to interface with the USB connection to the arduino.
	serial = new frc::SerialPort(BAUD, device, port);
	// We set the buffer size to 3, for each of the 3 color channel bytes.
	// We set the buffer to auto flush when it is full.
	serial->SetWriteBufferSize(3);
	serial->SetWriteBufferMode(frc::SerialPort::WriteBufferMode::kFlushWhenFull);
}

// Destructor, likely never called.
IndicatorLights::~IndicatorLights()
{
	// As serial is a pointer it is good practice to release the memory.
	// In practice this will usually have no effect.
	delete serial;
}

// Sets the LEDs to a predefined color from the COLOR enum.
void IndicatorLights::SetColor(COLOR color)
{
	switch (color)
	{
	case RED:
		SetColor(255, 0, 0);
		break;
	case GREEN:
		SetColor(0, 255, 0);
		break;
	case BLUE:
		SetColor(0, 0, 255);
		break;
	case YELLOW:
		SetColor(255, 255, 0);
		break;
	default:
		SetColor(0, 0, 0);
		break;
	}
}

// Sets the LEDs to a custom RGB color.
// Only the lower 8 bits are used.
// Basically only use numbers 0-255.
void IndicatorLights::SetColor(int r, int g, int b)
{
	// Create array to house each of our color channels.
	// We cast to char as SerialPort::Write() takes a char pointer.
	const char buffer [3] = { (char) r, (char) g, (char) b };
	// Convert the array into a pointer.
	const char* ptr = &buffer[0];
	// Send the bytes to the function.
	serial->Write(&ptr, 3);
	// Flush to ensure nothing lingered. This should do nothing but I like to be sure.
	serial->Flush();
}