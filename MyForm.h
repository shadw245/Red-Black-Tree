#pragma once
#include "RedBlackTreeWrapper.h"
#include <tuple>
using namespace RedBlackTreeWrapper;
using namespace std;



namespace RedBlackTreeGUImain {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			rbTree = gcnew RedBlackTreeManaged();
			animationTimer = gcnew Timer();
			animationTimer->Interval = 500; // Animation speed (500ms per step)
			animationTimer->Tick += gcnew EventHandler(this, &MyForm::AnimateStep);
			animationSteps = gcnew List<Tuple<String^, int>^>();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnInsert;
	private: System::Windows::Forms::Button^ btnDelete;
	private: System::Windows::Forms::Button^ btnSearch;
	private: System::Windows::Forms::TextBox^ txtInsert;
	private: System::Windows::Forms::TextBox^ txtDelete;
	private: System::Windows::Forms::Label^ txtOutput;
	private: System::Windows::Forms::Button^ btnDisplay;
	private: System::Windows::Forms::TextBox^ txtSearch;
	private: System::Windows::Forms::Panel^ pnlTree;
	private: Timer^ animationTimer;
	private: RedBlackTreeManaged^ rbTree;
	private: List<Tuple<String^, int>^>^ animationSteps;
	private: int searchValue = -1; // previously intio
	private: System::Windows::Forms::Label^ label1;
		   /// <summary>
		   /// Required designer variable.
		   /// </summary>
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->btnInsert = (gcnew System::Windows::Forms::Button());
			   this->btnDelete = (gcnew System::Windows::Forms::Button());
			   this->btnSearch = (gcnew System::Windows::Forms::Button());
			   this->txtInsert = (gcnew System::Windows::Forms::TextBox());
			   this->txtDelete = (gcnew System::Windows::Forms::TextBox());
			   this->txtOutput = (gcnew System::Windows::Forms::Label());
			   this->btnDisplay = (gcnew System::Windows::Forms::Button());
			   this->txtSearch = (gcnew System::Windows::Forms::TextBox());
			   this->pnlTree = (gcnew System::Windows::Forms::Panel());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->pnlTree->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // btnInsert
			   // 
			   this->btnInsert->BackColor = System::Drawing::Color::PowderBlue;
			   this->btnInsert->FlatAppearance->BorderColor = System::Drawing::Color::Blue;
			   this->btnInsert->ForeColor = System::Drawing::Color::Black;
			   this->btnInsert->Location = System::Drawing::Point(12, 10);
			   this->btnInsert->Name = L"btnInsert";
			   this->btnInsert->Size = System::Drawing::Size(81, 49);
			   this->btnInsert->TabIndex = 0;
			   this->btnInsert->Text = L"Insert";
			   this->btnInsert->UseVisualStyleBackColor = false;
			   this->btnInsert->Click += gcnew System::EventHandler(this, &MyForm::btnInsert_Click);
			   // 
			   // btnDelete
			   // 
			   this->btnDelete->BackColor = System::Drawing::Color::PowderBlue;
			   this->btnDelete->Location = System::Drawing::Point(246, 10);
			   this->btnDelete->Name = L"btnDelete";
			   this->btnDelete->Size = System::Drawing::Size(81, 49);
			   this->btnDelete->TabIndex = 1;
			   this->btnDelete->Text = L"Delete";
			   this->btnDelete->UseVisualStyleBackColor = false;
			   this->btnDelete->Click += gcnew System::EventHandler(this, &MyForm::btnDelete_Click);
			   // 
			   // btnSearch
			   // 
			   this->btnSearch->BackColor = System::Drawing::Color::PowderBlue;
			   this->btnSearch->Location = System::Drawing::Point(499, 10);
			   this->btnSearch->Name = L"btnSearch";
			   this->btnSearch->Size = System::Drawing::Size(81, 49);
			   this->btnSearch->TabIndex = 2;
			   this->btnSearch->Text = L"Search";
			   this->btnSearch->UseVisualStyleBackColor = false;
			   this->btnSearch->Click += gcnew System::EventHandler(this, &MyForm::btnSearch_Click);
			   // 
			   // txtInsert
			   // 
			   this->txtInsert->Location = System::Drawing::Point(99, 23);
			   this->txtInsert->Name = L"txtInsert";
			   this->txtInsert->Size = System::Drawing::Size(125, 22);
			   this->txtInsert->TabIndex = 3;
			   // 
			   // txtDelete
			   // 
			   this->txtDelete->Location = System::Drawing::Point(333, 23);
			   this->txtDelete->Name = L"txtDelete";
			   this->txtDelete->Size = System::Drawing::Size(137, 22);
			   this->txtDelete->TabIndex = 4;
			   // 
			   // txtOutput
			   // 
			   this->txtOutput->AutoSize = true;
			   this->txtOutput->BackColor = System::Drawing::Color::PaleTurquoise;
			   this->txtOutput->ForeColor = System::Drawing::Color::Maroon;
			   this->txtOutput->Location = System::Drawing::Point(44, 438);
			   this->txtOutput->Name = L"txtOutput";
			   this->txtOutput->Size = System::Drawing::Size(71, 16);
			   this->txtOutput->TabIndex = 6;
			   this->txtOutput->Text = L"Messages";
			   this->txtOutput->Click += gcnew System::EventHandler(this, &MyForm::txtOutput_Click);
			   // 
			   // btnDisplay
			   // 
			   this->btnDisplay->BackColor = System::Drawing::Color::PowderBlue;
			   this->btnDisplay->Location = System::Drawing::Point(929, 10);
			   this->btnDisplay->Name = L"btnDisplay";
			   this->btnDisplay->Size = System::Drawing::Size(86, 52);
			   this->btnDisplay->TabIndex = 7;
			   this->btnDisplay->Text = L"Display";
			   this->btnDisplay->UseVisualStyleBackColor = false;
			   this->btnDisplay->Click += gcnew System::EventHandler(this, &MyForm::btnDisplay_Click);
			   // 
			   // txtSearch
			   // 
			   this->txtSearch->Location = System::Drawing::Point(586, 23);
			   this->txtSearch->Name = L"txtSearch";
			   this->txtSearch->Size = System::Drawing::Size(137, 22);
			   this->txtSearch->TabIndex = 8;
			   // 
			   // pnlTree
			   // 
			   this->pnlTree->BackColor = System::Drawing::Color::Pink;
			   this->pnlTree->Controls->Add(this->txtOutput);
			   this->pnlTree->Location = System::Drawing::Point(15, 100);
			   this->pnlTree->Name = L"pnlTree";
			   this->pnlTree->Size = System::Drawing::Size(1128, 494);
			   this->pnlTree->TabIndex = 9;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->BackColor = System::Drawing::Color::LightBlue;
			   this->label1->ForeColor = System::Drawing::Color::Black;
			   this->label1->Location = System::Drawing::Point(12, 62);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(148, 16);
			   this->label1->TabIndex = 7;
			   this->label1->Text = L"enter -1 to stop program";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::SeaShell;
			   this->ClientSize = System::Drawing::Size(1155, 606);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->btnDisplay);
			   this->Controls->Add(this->pnlTree);
			   this->Controls->Add(this->txtSearch);
			   this->Controls->Add(this->txtDelete);
			   this->Controls->Add(this->txtInsert);
			   this->Controls->Add(this->btnSearch);
			   this->Controls->Add(this->btnDelete);
			   this->Controls->Add(this->btnInsert);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   this->pnlTree->ResumeLayout(false);
			   this->pnlTree->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

#pragma endregion

	private: void btnInsert_Click(System::Object^ sender, System::EventArgs^ e) {
		int value;
		if (Int32::TryParse(txtInsert->Text, value)) {
			if (value == -1) {
				// Stop the program
				Application::Exit();
			}
			else if (value < 0) {
				txtOutput->Text = "Error: Negative numbers other than -1 are not allowed.";
			}
			else {
				rbTree->Insert(value); // Insert valid positive numbers
				animationSteps = rbTree->GetAnimationSteps(); // Fetch animation steps
				StartAnimation(); // Start animation
				txtOutput->Text = "Inserted: " + value;
			}
		}
		else {
			txtOutput->Text = "Error: Invalid input for insertion.";
		}
	}


	private: void btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
		int value;
		if (Int32::TryParse(txtDelete->Text, value)) {
			bool exists = rbTree->Search(value);
			if (!exists) {
				txtOutput->Text = "Error: The number " + value + " does not exist in the tree.";
			}
			else {
				rbTree->Remove(value); // Remove the value from the tree
				animationSteps = rbTree->GetAnimationSteps(); // Fetch animation steps
				StartAnimation(); // Start animation
				txtOutput->Text = "Deleted: " + value;
			}
		}
		else {
			txtOutput->Text = "Error: Invalid input for deletion.";
		}
	}



	private: void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		int value;
		if (Int32::TryParse(txtSearch->Text, value)) {
			bool found = rbTree->Search(value);
			if (found) {
				searchValue = value; // Set the global searchValue to highlight the node
				txtOutput->Text = "Found: " + value;
				DisplayTree(); // Refresh the tree with the highlighted node
			}
			else {
				txtOutput->Text = "Not Found: " + value;
			}
		}
		else {
			txtOutput->Text = "Error: Invalid input for search.";
		}
	}


	private: void btnDisplay_Click(System::Object^ sender, System::EventArgs^ e) {
		DisplayTree(); 
		txtOutput->Text = "Tree displayed.";
	}

	private: void DisplayTree() {
		Graphics^ g = pnlTree->CreateGraphics();
		g->Clear(System::Drawing::Color::Pink); // Clear panel
		DrawNode(g, rbTree->GetRootData(), pnlTree->Width / 2, 20, pnlTree->Width / 4, nullptr);
	}

	private: void DrawNode(Graphics^ g, int nodeData, int x, int y, int offset, Tuple<int, int>^ parentCoords) {
		if (nodeData == -1) return; // Handle null nodes

		// Determine if the node is being searched
		bool isSearchedNode = (nodeData == searchValue); // searchValue is updated during search

		// Determine node color (red/black) for the fill
		bool isRed = rbTree->IsNodeRed(nodeData);
		Brush^ brush = isRed ? Brushes::Red : Brushes::Black;

		// Draw the node as a filled circle
		g->FillEllipse(brush, x - 15, y - 15, 30, 30);

		// Add a green border if the node is being searched
		if (isSearchedNode) {
			Pen^ greenPen = gcnew Pen(System::Drawing::Color::Green, 3);
			g->DrawEllipse(greenPen, x - 15, y - 15, 30, 30);
		}

		// Draw the node's data
		g->DrawString(nodeData.ToString(), gcnew System::Drawing::Font("Arial", 12), Brushes::White, x - 10, y - 10);

		// Draw a line to the parent if applicable
		if (parentCoords != nullptr) {
			g->DrawLine(Pens::Black, parentCoords->Item1, parentCoords->Item2, x, y);
		}

		// Recursively draw left and right child nodes
		auto leftData = rbTree->GetLeftChild(nodeData);
		auto rightData = rbTree->GetRightChild(nodeData);
		if (leftData != -1) {
			DrawNode(g, leftData, x - offset, y + 50, offset / 2, gcnew Tuple<int, int>(x, y));
		}
		if (rightData != -1) {
			DrawNode(g, rightData, x + offset, y + 50, offset / 2, gcnew Tuple<int, int>(x, y));
		}
	}




	private: void StartAnimation() {
		if (animationSteps->Count > 0) {
			animationTimer->Start();
		}
	}

	private: void AnimateStep(Object^ sender, EventArgs^ e) {
		if (animationSteps->Count > 0) {
			// Fetch the next animation step
			auto step = animationSteps[0];
			animationSteps->RemoveAt(0);

			// Extract the action and value from the step
			String^ action = step->Item1; // e.g., "RotateLeft", "Recolor"
			int nodeValue = step->Item2;  // Node value to animate

			// Update the output text with the current step
			txtOutput->Text = "Animating: " + action + " on Node " + nodeValue.ToString();

			// Perform graphical updates based on the action
			if (action == "RotateLeft" || action == "RotateRight") {
				// For rotations, redraw the tree structure to reflect changes
				DisplayTree();
			}
			else if (action == "Recolor") {
				// For recoloring, update the color of the node in the display
				DisplayTree(); // Optionally add custom handling for recolor animation
			}
			else {
				// Handle other actions if necessary
			}
		}
		else {
			// If no more steps, stop the animation timer and refresh the tree display
			animationTimer->Stop();
			DisplayTree();
			txtOutput->Text = "Animation complete!";
		}
	}

private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void txtOutput_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
[STAThread]
int main()
{
	// Enable visual styles for the application
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

	// Create and run the main form
	RedBlackTreeGUImain::MyForm^ mainForm = gcnew RedBlackTreeGUImain::MyForm();
	System::Windows::Forms::Application::Run(mainForm);
	return 0;
}




