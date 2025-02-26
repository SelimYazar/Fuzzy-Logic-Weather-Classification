//Selim Can Yazar 152120191023 Hw1


#include <iostream>
using namespace std;

// Sıcaklık için üyelik fonksiyonunu hesaplayan fonksiyon
double calculateTemperatureMembership(int temperature) {
    if (temperature <= 0) {
        cout << "Hava soğuk." << endl;
        return 1.0; // Soğuk için üyelik derecesi 1
    } else if (temperature > 0 && temperature < 15) {
        cout << "Hava ılık." << endl;
        return double(temperature) / 15; // Ilık için üyelik derecesi, lineer interpolasyon
    } else if (temperature >= 15 && temperature <= 30) {
        cout << "Hava sıcak." << endl;
                return double(temperature - 15) / 15; // Sıcak için üyelik derecesi, lineer interpolasyon
    } else { // temperature > 30
        cout << "Hava çok sıcak." << endl;
        return 1.0; // Çok sıcak için üyelik derecesi 1
    }
}

// Nem için üyelik fonksiyonunu hesaplayan fonksiyon
double calculateHumidityMembership(int humidity) {
    if (humidity <= 30) {
        cout << "Hava hafif nemli." << endl;
        return 1.0;  // Hafif nemli için üyelik derecesi 1
    } else if (humidity > 30 && humidity <= 60) {
        cout << "Hava nemli." << endl;
        return double(humidity - 30) / 30;  // Nemli için üyelik derecesi, lineer interpolasyon
    } else if (humidity > 60 && humidity <= 90) {
        cout << "Hava çok nemli." << endl;
        return double(humidity - 60) / 30;  // Çok nemli için üyelik derecesi, lineer interpolasyon
    } else { // humidity > 90
        cout << "Hava aşırı nemli." << endl;
        return 1.0;  // Aşırı nemli için üyelik derecesi 1
    }
}

int main() {
    int temperature, humidity;

    // Kullanıcıdan sıcaklık ve nem değerlerini al
    cout << "Lütfen hava sıcaklığını giriniz (derece cinsinden): ";
    cin >> temperature;
    cout << "Lütfen nem oranını giriniz (% cinsinden): ";
    cin >> humidity;

    // Sıcaklık ve nem için üyelik derecelerini hesapla ve göster
    double temperatureMembership = calculateTemperatureMembership(temperature);
    double humidityMembership = calculateHumidityMembership(humidity);

    cout << "Sıcaklık üyelik derecesi: " << temperatureMembership << endl;
    cout << "Nem üyelik derecesi: " << humidityMembership << endl;

    return 0;
}
