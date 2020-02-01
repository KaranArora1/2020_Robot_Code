#include "frc/SerialPort.h"

// Formerly STSLSHost
class IndicatorLights
{
public:
	enum COLOR { NONE = 0, RED, GREEN, BLUE, YELLOW };

	IndicatorLights(const wpi::Twine&, frc::SerialPort::Port);
	~IndicatorLights();
	
	void SetColor(COLOR);
	void SetColor(int, int, int);
private:
	// Baud is the speed of data transfer in bits/second.
	static constexpr int BAUD = 9600;
	
	frc::SerialPort* serial;
};