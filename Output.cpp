#include "Output.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main2() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUISEMESTERPROJECT::Output form;
	Application::Run(% form);
}