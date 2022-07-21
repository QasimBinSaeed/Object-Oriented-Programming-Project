#include "Input.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main1() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUISEMESTERPROJECT::Input form;
	Application::Run(% form);
}