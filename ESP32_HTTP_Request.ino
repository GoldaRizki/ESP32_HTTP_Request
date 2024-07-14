#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const char* ssid = "NAMA_WIFI_MU";
const char* password = "PASSWORD_WIFI_MU";

String serverName;

String data_body;
JsonDocument data_sensor;

unsigned long waktuTerakhir = 0;
unsigned long delayTimer = 7500; //delay perngiriman data (dalam milidetik/milisecond)


void setup() {
  // put your setup code here, to run once:


  // ENDPOINT UNTUK NGIRIM KE SERVER
  // (silahkan uncomment kalo mau dipake)
  // Jangan lupa IP address nya diubah dulu pake IP komputermu yg jadi Server

  //serverName = "http://IP_ADDRESS_KOMPUTER_MU/api/si_paling_skripsi";  // Ini untuk ngirim data beneran ke server
  serverName = "http://IP_ADDRESS_KOMPUTER_MU/api/data_random";  // Ini kalo mau datanya dikasih data dummy/random 

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Menghubungkan . . . ");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Terhubung dengan IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println(" 5 detik lagi akan mengirimkan data");  


}

void loop() {
  // put your main code here, to run repeatedly:


    /*

          Silahkan masukkan codingan yang lain ke sini....
          (Proses membaca data dari power meter dan tetek bengek nya masuk ke sini)

    */


    if ((millis() - waktuTerakhir) > delayTimer) {
      //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
        WiFiClient client;
        HTTPClient http;
      
        // Your Domain name with URL path or IP address with path
        http.begin(client, serverName);


        /*
         BAGIAN NGIRIM DATA KE SERVER 
         Semua hasil pengukuran tinggal di assign dibawah ini
        */
        
        data_sensor["tegangan"] = 0;      // Misal udah dapet nilai tegangan, assign aja kesitu... (ganti angka nol dengan nilai tegangan)
        data_sensor["arus"] = 0;          // Begitu juga nilai arus. Kalo udah dapet nilai arusnya, tinggal assign gantiin angka nol aja...
        data_sensor["faktor_daya"] = 0;
        data_sensor["daya_aktif"] = 0;
        data_sensor["daya_reaktif"] = 0;
        data_sensor["daya_semu"] = 0;
        data_sensor["total_daya_aktif"] = 0;
        data_sensor["total_daya_reaktif"] = 0;
        data_sensor["total_daya_semu"] = 0;
        data_sensor["total_faktor_daya"] = 0;
        data_sensor["frekuensi"] = 0;
        data_sensor["reactive_power_demand"] = 0;
        data_sensor["apparent_power_demand"] = 0;

        serializeJson(data_sensor, data_body);


        // WES, BAGIAN IKI RAK SAH DIURUSI
        
        // Specify content-type header
        http.addHeader("Content-Type", "application/json");
        // Data to send with HTTP POST
      

        // Send HTTP POST request
        int httpResponseCode = http.POST(data_body);
        

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);


          
        // Free resources
        http.end();
      }
      else {
        Serial.println("WiFi Terputus");
      }
      waktuTerakhir = millis();
    }
    

}
