#include <cmath>
#include <iostream>
#include <Windows.h>
#include <string>

using namespace System;
using namespace System::Windows::Forms;

// Declaration of the Triangle class
public ref class Triangle {
protected:
    double sideA;
    double sideB;
    double sideC;

public:
    // Constructor to initialize the sides of the triangle
    Triangle(double a, double b, double c) : sideA(a), sideB(b), sideC(c) {
        // Check if the sides form a valid triangle
        if (!IsValid()) {
            throw gcnew System::ArgumentException("Invalid sides for a triangle");
        }
    }

    // Method to calculate and return the perimeter of the triangle
    double GetPerimeter() {
        return sideA + sideB + sideC;
    }

    // Virtual method to calculate angles in a generic triangle
    virtual void CalculateAngles() {
        // Implement angle calculation logic for a generic triangle if needed
    }

private:
    // Helper method to check if the sides form a valid triangle
    bool IsValid() {
        return (sideA + sideB > sideC) && (sideA + sideC > sideB) && (sideB + sideC > sideA);
    }
};

// Declaration of the Rightangled class as a derived class from Triangle
public ref class Rightangled : public Triangle {
private:
    double area;

public:
    // Constructor to initialize the sides and calculate the area of the right-angled triangle
    Rightangled(double a, double b, double c) : Triangle(a, b, c) {
        CalculateArea();
    }

    // Method to calculate and return the area of the right-angled triangle
    void CalculateArea() {
        area = 0.5 * sideA * sideB;
    }

    double GetArea() {
        return area;
    }

    // Override the base class method to include angle calculation specific to a right-angled triangle
    virtual void CalculateAngles() override {
        // Implement angle calculation logic for a right-angled triangle if needed
    }
};

// Declaration of the main form
public ref class MainForm : public Form {
private:
    Label^ labelSideA;
    Label^ labelSideB;
    Label^ labelSideC;
    TextBox^ textBoxSideA;
    TextBox^ textBoxSideB;
    TextBox^ textBoxSideC;
    Button^ calculateButton;
    Label^ labelPerimeter;
    Label^ labelArea;

public:
    MainForm() {
        InitializeComponents();
    }

private:
    // Method to initialize and configure the form controls
    void InitializeComponents() {
        // Example:
        labelSideA = gcnew Label();
        labelSideA->Text = "Side A:";
        labelSideA->Location = System::Drawing::Point(20, 20);

        labelSideB = gcnew Label();
        labelSideB->Text = "Side B:";
        labelSideB->Location = System::Drawing::Point(20, 60);

        labelSideC = gcnew Label();
        labelSideC->Text = "Side C:";
        labelSideC->Location = System::Drawing::Point(20, 100);

        textBoxSideA = gcnew TextBox();
        textBoxSideA->Location = System::Drawing::Point(120, 20);

        textBoxSideB = gcnew TextBox();
        textBoxSideB->Location = System::Drawing::Point(120, 60);

        textBoxSideC = gcnew TextBox();
        textBoxSideC->Location = System::Drawing::Point(120, 100);

        calculateButton = gcnew Button();
        calculateButton->Location = System::Drawing::Point(20, 140);
        calculateButton->Text = "Calculate";
        calculateButton->Click += gcnew EventHandler(this, &MainForm::CalculateButtonClick);

        labelPerimeter = gcnew Label();
        labelPerimeter->Location = System::Drawing::Point(20, 180);

        labelArea = gcnew Label();
        labelArea->Location = System::Drawing::Point(20, 220);

        // Add controls to the form
        this->Controls->Add(labelSideA);
        this->Controls->Add(labelSideB);
        this->Controls->Add(labelSideC);
        this->Controls->Add(textBoxSideA);
        this->Controls->Add(textBoxSideB);
        this->Controls->Add(textBoxSideC);
        this->Controls->Add(calculateButton);
        this->Controls->Add(labelPerimeter);
        this->Controls->Add(labelArea);
    }

    // Event handler for the "Calculate" button
    void CalculateButtonClick(Object^ sender, EventArgs^ e) {
        try {
            // Get user input from textboxes
            double sideA = Convert::ToDouble(textBoxSideA->Text);
            double sideB = Convert::ToDouble(textBoxSideB->Text);
            double sideC = Convert::ToDouble(textBoxSideC->Text);

            // Create instances of the classes
            Triangle^ triangle = gcnew Triangle(sideA, sideB, sideC);
            Rightangled^ rightangled = gcnew Rightangled(sideA, sideB, sideC);

            // Display results
            labelPerimeter->Text = "Perimeter: " + (triangle->GetPerimeter()).ToString();
            labelArea->Text = "Area: " + (rightangled->GetArea()).ToString();
        }
        catch (System::Exception^ ex) {
            MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
};

// Entry point for the application
[STAThread]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Create and run the main form
    Application::Run(gcnew MainForm());

    return 0;
}
