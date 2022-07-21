#pragma once
#include"SimulationModule.h"
#include"PlantGrowthModule.h"
#include"SoilWaterModule.h"
#include"WeatherModule.h"
#include<string.h>
#include"Input.h"
#include"Output.h"
namespace GUISEMESTERPROJECT {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Simulation
	/// </summary>
	public ref class Simulation : public System::Windows::Forms::Form
	{
	public:
		Simulation(void)
		{
			obj = new SimulationModule;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Simulation()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;

	private: SimulationModule *obj;
	//

	private: System::Windows::Forms::Button^ btn_start;
	private: System::Windows::Forms::Button^ btn_stop;
	private: System::Windows::Forms::Button^ button1;


	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label3;
	private: System::ComponentModel::IContainer^ components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Simulation::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btn_start = (gcnew System::Windows::Forms::Button());
			this->btn_stop = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(20, 10);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(507, 26);
			this->label1->TabIndex = 0;
			this->label1->Text = L"CROP GROWTH MODEL AND SIMULATION";
			// 
			// btn_start
			// 
			this->btn_start->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_start->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_start->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_start.Image")));
			this->btn_start->Location = System::Drawing::Point(25, 190);
			this->btn_start->Name = L"btn_start";
			this->btn_start->Size = System::Drawing::Size(107, 48);
			this->btn_start->TabIndex = 2;
			this->btn_start->Text = L"Start";
			this->btn_start->UseVisualStyleBackColor = true;
			this->btn_start->Click += gcnew System::EventHandler(this, &Simulation::button4_Click);
			// 
			// btn_stop
			// 
			this->btn_stop->BackColor = System::Drawing::Color::Transparent;
			this->btn_stop->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_stop.BackgroundImage")));
			this->btn_stop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_stop->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_stop->ForeColor = System::Drawing::Color::Black;
			this->btn_stop->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_stop.Image")));
			this->btn_stop->Location = System::Drawing::Point(423, 190);
			this->btn_stop->Name = L"btn_stop";
			this->btn_stop->Size = System::Drawing::Size(107, 48);
			this->btn_stop->TabIndex = 3;
			this->btn_stop->Text = L"Stop";
			this->btn_stop->UseVisualStyleBackColor = false;
			this->btn_stop->Click += gcnew System::EventHandler(this, &Simulation::btn_stop_Click);
			// 
			// button1
			// 
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(278, 190);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 48);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Result";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Simulation::button1_Click);
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(151, 190);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 48);
			this->button2->TabIndex = 16;
			this->button2->Text = L"Input";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Simulation::button2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::Window;
			this->label2->Location = System::Drawing::Point(21, 59);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(126, 24);
			this->label2->TabIndex = 17;
			this->label2->Text = L"Select Crop :";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Wheat", L"Corn", L"Sunflower", L"Rice", L"Cotton" });
			this->comboBox1->Location = System::Drawing::Point(169, 65);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(140, 22);
			this->comboBox1->TabIndex = 18;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(25, 131);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(505, 38);
			this->progressBar1->TabIndex = 19;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Simulation::timer1_Tick);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::Window;
			this->label3->Location = System::Drawing::Point(395, 65);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(74, 24);
			this->label3->TabIndex = 20;
			this->label3->Text = L"DAY: 1";
			// 
			// Simulation
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 14);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(556, 265);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btn_stop);
			this->Controls->Add(this->btn_start);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Simulation";
			this->Text = L"CROP GROWTH MODEL AND SIMULATION";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		static int day = 0;
		day++;
		label3->Text = "DAY: " + day.ToString();
		progressBar1->Value = 0;
		timer1->Start();

		float pint_val = (obj->pint());
		float intot_val = (obj->intot());
		if (pint_val == intot_val)
		{
			MessageBox::Show("Plant is Matured", "Your Application Name", MessageBoxButtons::OKCancel);
		}
		obj->Initialization();
		//Starting Execution from here
		for (int i = 0; i < 3; i++)
		{
			obj->rateCalculations();
			obj->Integration();
			obj->Output();
		}
		obj->Close();
	}
private: System::Void btn_stop_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (MessageBox::Show("Do you want to exit?", "Exit", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
	{
		Application::Exit();
	}
	else
	{

	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	float lai_val = (obj->getLai());
	float w_val = (obj->w());
	float wc_val = (obj->wc());
	float wr_val = (obj->wr());
	float wf_val = (obj->wf());
	float N_val = (obj->N());
	float SRAD_val = (obj->SRAD());
	float TMAX_val = (obj->TMAX());
	float TMIN_val = (obj->TMIN());
	float RAIN_val = (obj->RAIN());
	float IRR_val = (obj->IRR());
	float ROF_val = (obj->ROF());
	float DP_val = (obj->DP());
	float INF_val = (obj->RAIN());
	float DRN_val = (obj->INF());
	float ETp_val = (obj->ETp());
	float ESa_val = (obj->ESa());
	float EPa_val = (obj->EPa());
	float SWC_val = (obj->SWC());
	float SWFAC1_val = (obj->SWFAC1());
	float SWFAC2_val = (obj->SWFAC2());
	Output^ f = gcnew Output();
	f->Values(lai_val, w_val, wc_val, wr_val, wf_val, N_val, SRAD_val, TMAX_val, TMIN_val, RAIN_val, IRR_val, ROF_val, DP_val, INF_val, DRN_val,ETp_val,ESa_val,EPa_val,SWC_val,SWFAC1_val,SWFAC2_val);
	f->ShowDialog();
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
{
	Input^ f2 = gcnew Input();
	f2->ShowDialog();

}

private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

	progressBar1->Increment(6);

	if (progressBar1->Value == 100) {
	
		timer1->Stop();
		//Message Box for Completion
	
	}

}
};
}