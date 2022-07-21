#include "Simulation.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUISEMESTERPROJECT::Simulation form;
	Application::Run(% form);
}