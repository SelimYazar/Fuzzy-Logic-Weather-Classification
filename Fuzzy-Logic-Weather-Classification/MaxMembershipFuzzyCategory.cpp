#include <iostream>
#include <string>
using namespace std;

double calculateTemperatureMembership(int temperature) {
    if (temperature <= 0) {
        cout << "Hava soğuk." << endl;
        return 1.0; 
    } else if (temperature > 0 && temperature < 15) {
        cout << "Hava ılık." << endl;
        return static_cast<double>(temperature) / 15; 
    } else if (temperature >= 15 && temperature <= 30) {
        cout << "Hava sıcak." << endl;
        return static_cast<double>(temperature - 15) / 15; 
    } else { // temperature > 30
        cout << "Hava çok sıcak." << endl;
        return 1.0; 
    }
}

double calculateHumidityMembership(int humidity) {
    if (humidity <= 30) {
        cout << "Hava hafif nemli." << endl;
        return 1.0;  
    } else if (humidity > 30 && humidity <= 60) {
        cout << "Hava nemli." << endl;
        return static_cast<double>(humidity - 30) / 30;  
    } else if (humidity > 60 && humidity <= 90) {
        cout << "Hava çok nemli." << endl;
        return static_cast<double>(humidity - 60) / 30;  
    } else { // humidity > 90
        cout << "Hava aşırı nemli." << endl;
        return 1.0;  
    }
}

void printFuzzyCategory(double temperatureMembership, double humidityMembership) {
    // 3x3'lük karar matrisi tanımlanması
    string fuzzyCategories[3][3] = {
        {"kotu3", "iyi1", "iyi2"},
        {"normal1", "iyi3", "kotu1"},
        {"normal2", "normal3", "kotu2"}
    };

    // Sıcaklık ve nem kümelerindeki maksimum üyelik derecesini bul
    double maxMembership = max(temperatureMembership, humidityMembership);

    // Sıcaklık ve nem üyelik derecelerinden hangisi maksimumsa ona göre sonucu belirle
    string resultCategory;
    if (maxMembership == temperatureMembership) {
        resultCategory = "Sıcaklık";
    } else {
        resultCategory = "Nem";
    }

    // Matristen kategoriyi seç
    int tempCategory = static_cast<int>(temperatureMembership * 2);  // 0, 1, 2 olarak indeksleme yapar
    int humCategory = static_cast<int>(humidityMembership * 2);  // 0, 1, 2 olarak indeksleme yapar
    string result = fuzzyCategories[tempCategory][humCategory];

    // Sonucu ve maksimum üyelik derecesini yazdır
    cout << "Hava Durumu: " << result << ", üyelik derecesi = " << maxMembership << " (" << resultCategory << " üyelik)" << endl;
}

int main() {
    int temperature, humidity;

    // Kullanıcıdan sıcaklık ve nem değerlerini al
    cout << "Lütfen hava sıcaklığını giriniz (derece cinsinden): ";
    cin >> temperature;
    cout << "Lütfen nem oranını giriniz (% cinsinden): ";
    cin >> humidity;

    // Sıcaklık ve nem için üyelik derecelerini hesapla
    double temperatureMembership = calculateTemperatureMembership(temperature);
    double humidityMembership = calculateHumidityMembership(humidity);

    cout << "Sıcaklık üyelik derecesi: " << temperatureMembership << endl;
    cout << "Nem üyelik derecesi: " << humidityMembership << endl;

    // Bulanık kategoriye göre sonucu yazdır (maksimum üyelik derecesi kullanılarak)
    printFuzzyCategory(temperatureMembership, humidityMembership);

    return 0;
}

