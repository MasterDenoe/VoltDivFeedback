// VoltDividerSolution.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// *********** BY: DEAN PRICE 17/04/2024 ***************

#include <iostream>
#include <cmath>
#include <cstdlib>
using std::cout, std::endl, std::cin;


// Description:
// Vref -> R1 -> Vr -> R2 -> GND    (R1 & R2 are in series across Vref with Vr being the voltage divided)
// Vout -> R3 -> Vfb -> R4 -> GND   (R3 & R4 are in series across Vout with Vfb being the voltage divided)
// Solution gives Vout such that Vfb == Vr

// frm are all resistance values
// vref is the feedback voltage reference coming from controller
// vout is target output voltage


int main()
{
    double vref = 5.1;
    double vout = 385.0;
    double fra[4] = { 10.0, 22.0, 47.0, 68.0 };
    const int max_power = 5;
    const int base_vals = sizeof(fra) / 8;
    double frm[base_vals*max_power] = { 0 };    
    int nov = sizeof(frm) / 8;                  // number of total different numbers

    cout << "Please input the controllers reference voltage: ";
    cin >> vref;
    //system("CLS");
    cout << "Please input the desired output voltage: ";
    cin >> vout;
    //system("CLS");

    int runner = 0;     // runner is to fill frm sequentially without using iii or jjj which cant be done?
    for (int iii = 1; iii <= base_vals; iii++)  // to run through fra
    {
        for (int jjj = 1; jjj <= max_power; jjj++)  // to raise the power greater every itteration
        {
            double scale = pow(10, jjj - 1);
            frm[runner] = scale * fra[iii - 1];
            runner++;
        }
    }
    cout << "***********************************************" << endl;

    double r1 = frm[0];
    double r2 = frm[0];
    double r3 = frm[0];
    double r4 = frm[0];
    double best_r1 = 1.0;
    double best_r2 = 1.0;
    double best_r3 = 1.0;
    double best_r4 = 1.0;

    double real_vout = 0.0;
    double best_vout = 0.0;
    double min_error = 999;
    double error_volt = 99.9;
    double run_error_per = 0.0;

    for (int iii = 0; iii < nov; iii++)
    {
        r1 = frm[iii];
        for (int jjj = 0; jjj < nov; jjj++)
        {
            r2 = frm[jjj];
            for (int kkk = 0; kkk < nov; kkk++)
            {
                r3 = frm[kkk];
                for (int lll = 0; lll < nov; lll++)
                {
                    r4 = frm[lll];
                    // determining if better option
                    real_vout = vref * (r4 / r2) * (r1 + r2) / (r3 + r4);
                    run_error_per = 100 * (real_vout - vout) / vout;

                    //if (abs(run_error_per) < 1) { cout << run_error_per << endl; };
                    

                    //cout << r1 << " " << r2 << " " << r3 << " " << r4 << " " << endl;
                    if (abs(run_error_per) < abs(min_error))
                    {
                        best_vout = real_vout;
                        min_error = run_error_per;
                        best_r1 = r1; best_r2 = r2;
                        best_r3 = r3; best_r4 = r4;
                    }
                }
            }
        }
        //cout << "Status: " << 100*iii/nov << "%" << endl;
    }


    cout << "Minimum error found ";
    cout << "in percentage = " << min_error;
    cout << "%" << endl;

    cout << "Voltage Output = ";
    cout << (best_vout);
    cout << "V" << endl;

    cout << "Voltage difference = ";
    cout << (best_vout - vout);
    cout << "V" << endl;

    cout << "Best Values:" << endl;
    cout << "  R1 = " << best_r1 << endl;
    cout << "  R2 = " << best_r2 << endl << endl;
    cout << "  R3 = " << best_r3 << endl;
    cout << "  R4 = " << best_r4 << endl;
    //cout << sizeof(frm)/8 << endl;

    cout << endl << "Press enter to end program... ";
    //cin.get(); // clearing the new line char from the buffer from last cin
    cin.ignore(); // clearing the new line char from the buffer from last cin
    cin.get();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
