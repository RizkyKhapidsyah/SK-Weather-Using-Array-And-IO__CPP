#pragma warning(disable:4996)

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct Weather {
    double tempF;
    double windSpeed;
    double dewPoint;
    double windChill;
    double cloudBase;
};

int i = 0;

void get_input(Weather calculation[]);
void get_windChill(Weather* calculation);
void get_cloudBase(Weather* calculation);
void show_output(Weather calculation[]);

int main() {
    Weather calculation[20];
    get_input(calculation); //input from file
    show_output(calculation);
    return 0;
}

void show_output(Weather calculation[]) {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);
    cout << endl;
    cout << "    Temperature   Wind Speed   Dew Point   Wind Chill    Cloud Base" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int j = 0; j <= i; j++) {
        if ((calculation[j].tempF < 50) && (calculation[j].windSpeed > 3))
            cout << std::right << std::setw(10) << calculation[j].tempF << " dF" << std::setw(10)
            << calculation[j].windSpeed << " mph " << std::setw(10)
            << calculation[j].dewPoint << " dF" << std::setw(10) << calculation[j].windChill
            << " dF" << std::setw(10) << calculation[j].cloudBase << " ft" << endl;

        else
        {
            cout << std::right << std::setw(10) << calculation[j].tempF << " dF" << std::setw(10)
                << calculation[j].windSpeed << " mph " << std::setw(10)
                << calculation[j].dewPoint << " dF" << std::setw(10) << "  ***"
                << " dF" << std::setw(10) << calculation[j].cloudBase << " ft" << endl;
        }
    }

    cout << "\n\n*** Temperature must be 50 degree or less., and";
    cout << "\nwindspeed must be >3 mp h to compute wind chill.";
}

void get_input(Weather* ptr) {
    cout << endl;
    cout << " _______________________________________________________________" << endl;
    cout << " |                        |" << endl;
    cout << " | This program determines wind chill using temperature  |" << endl;
    cout << " | In Fahrenheit and wind speed in mph, and computes     |" << endl;
    cout << " | The cloud base using the dew point in Fahrenheit    |" << endl;
    cout << " |______________________________________________________________ " << endl;

    ifstream obj("weatherData.txt");

    if (obj) {
        string value;
        double tempF = 0;
        double windSpeed = 0;
        double dewPoint = 0;
        
        while (getline(obj, value)) {


            tempF = atof(value.c_str());
            ptr->tempF = tempF;

            value.clear();
            getline(obj, value);
            windSpeed = atof(value.c_str());
            ptr->windSpeed = windSpeed;

            value.clear();
            getline(obj, value);
            dewPoint = atof(value.c_str());
            ptr->dewPoint = dewPoint;

            tempF = 0;
            windSpeed = 0;
            dewPoint = 0;
            value.clear();

            get_windChill(ptr);
            get_cloudBase(ptr);
            ptr++;
            i++;
        }
        
    } else {
        cout << "\n Error : Unable to open `weatherData.txt` file";
    }
    

}

void get_windChill(Weather* calculation) {
    double windChill = 0.0;
    windChill = 35.74 + (0.6215 * calculation->tempF) - (35.75 * (pow(calculation->windSpeed, 0.16))) +
        ((0.4275 * calculation->tempF) * (pow(calculation->windSpeed, 0.16)));
    calculation->windChill = windChill;
}

void get_cloudBase(Weather* calculation) {
    double cloudBase = 0.0;
    cloudBase = ((calculation->tempF - calculation->dewPoint) / 4.4 * 1000);
    calculation->cloudBase = cloudBase;
}