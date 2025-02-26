#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Define the membership functions for temperature
double coldTemperatureMembership(int temperature) {
    if (temperature <= 0) return 1.0;
    if (temperature > 0 && temperature < 15) return (15.0 - temperature) / 15.0;
    return 0.0;
}

double warmTemperatureMembership(int temperature) {
    if (temperature > 0 && temperature < 15) return static_cast<double>(temperature) / 15.0;
    if (temperature >= 15 && temperature <= 30) return (30.0 - temperature) / 15.0;
    return 0.0;
}

double hotTemperatureMembership(int temperature) {
    if (temperature >= 15 && temperature <= 30) return (static_cast<double>(temperature) - 15) / 15.0;
    if (temperature > 30) return 1.0;
    return 0.0;
}

// Define the membership functions for humidity
double lowHumidityMembership(int humidity) {
    if (humidity <= 30) return 1.0;
    if (humidity > 30 && humidity <= 60) return (60.0 - humidity) / 30.0;
    return 0.0;
}

double mediumHumidityMembership(int humidity) {
    if (humidity > 30 && humidity <= 60) return (static_cast<double>(humidity) - 30) / 30.0;
    if (humidity > 60 && humidity <= 90) return (90.0 - humidity) / 30.0;
    return 0.0;
}

double highHumidityMembership(int humidity) {
    if (humidity > 60 && humidity <= 90) return (static_cast<double>(humidity) - 60) / 30.0;
    if (humidity > 90) return 1.0;
    return 0.0;
}

// Define the fuzzy rules and apply them to determine the weather condition
string applyFuzzyRules(double coldTemp, double warmTemp, double hotTemp, double lowHum, double medHum, double highHum) {
    // Fuzzy categories as defined in the problem
    string fuzzyCategories[3][3] = {
        {"kotu3", "iyi1", "iyi2"},
        {"normal1", "iyi3", "kotu1"},
        {"normal2", "normal3", "kotu2"}
    };

    // Find the maximum membership degrees
    double maxTempMembership = max({coldTemp, warmTemp, hotTemp});
    double maxHumMembership = max({lowHum, medHum, highHum});

    // Determine the fuzzy category
    int tempCategory = (coldTemp > warmTemp) ? ((coldTemp > hotTemp) ? 0 : 2) : ((warmTemp > hotTemp) ? 1 : 2);
    int humCategory = (lowHum > medHum) ? ((lowHum > highHum) ? 0 : 2) : ((medHum > highHum) ? 1 : 2);

    return fuzzyCategories[humCategory][tempCategory];
}

// Perform defuzzification using the Centroid Method considering both temperature and humidity
double defuzzify(double coldTemp, double warmTemp, double hotTemp, double lowHum, double medHum, double highHum) {
    double tempNumerator = (coldTemp * 0 + warmTemp * 15 + hotTemp * 30);
    double tempDenominator = (coldTemp + warmTemp + hotTemp);
    double humidityNumerator = (lowHum * 30 + medHum * 60 + highHum * 90);
    double humidityDenominator = (lowHum + medHum + highHum);
    
    double tempCentroid = (tempDenominator == 0.0) ? 0.0 : (tempNumerator / tempDenominator);
    double humidityCentroid = (humidityDenominator == 0.0) ? 0.0 : (humidityNumerator / humidityDenominator);

    return (tempCentroid + humidityCentroid) / 2.0;
}

int main() {
    int temperature, humidity;

    // Get temperature and humidity values from the user
    cout << "Lütfen hava sıcaklığını giriniz (derece cinsinden): ";
    cin >> temperature;
    cout << "Lütfen nem oranını giriniz (% cinsinden): ";
    cin >> humidity;

    // Calculate the membership degrees for temperature
    double cold = coldTemperatureMembership(temperature);
    double warm = warmTemperatureMembership(temperature);
    double hot = hotTemperatureMembership(temperature);

    // Calculate the membership degrees for humidity
    double low = lowHumidityMembership(humidity);
    double medium = mediumHumidityMembership(humidity);
    double high = highHumidityMembership(humidity);

    cout << "Sıcaklık üyelik dereceleri: Cold = " << cold << ", Warm = " << warm << ", Hot = " << hot << endl;
    cout << "Nem üyelik dereceleri: Low = " << low << ", Medium = " << medium << ", High = " << high << endl;

    // Apply fuzzy rules and get the fuzzy category
    string fuzzyCategory = applyFuzzyRules(cold, warm, hot, low, medium, high);
    cout << "Hava Durumu: " << fuzzyCategory << endl;

    // Perform defuzzification considering both temperature and humidity
    double crispOutput = defuzzify(cold, warm, hot, low, medium, high);
    cout << "Berraklaştırılmış Değer(Hissedilen sıcaklık): " << crispOutput << endl;

    return 0;
}



