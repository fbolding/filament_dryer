//==============================================================
// Filename : webUI.cpp
// Authors : Freek Bolding
// Description : Source file for simple control through web interface
//==============================================================

#include "webUI.h"
#include "secrets.h"

//Settings
#define SLOW_BOOT 0
#define HOSTNAME "ESPUITest"
#define FORCE_USE_HOTSPOT 0

// Global 
extern dryerAPI api;

//Function Prototypes
void connectWifi();
void setUpUI();
void generalCallback(Control *sender, int type);


//UI handles
uint16_t wifi_ssid_text, wifi_pass_text;
uint16_t tempLabel, humidLabel; // Show information
uint16_t fanSwitch, heatSwitch; // Switches
uint16_t tempSlider; // Temperature Reference input
volatile bool updates = false;

webUI::webUI(dryerAPI * _dryerAPIPtr){
    dryerAPIPtr = _dryerAPIPtr;
}

void webUI::setup(){
    randomSeed(0);
	connectWifi();
	WiFi.setSleep(false); //Turn off sleeping to increase UI responsivness (at the cost of power use)
	setUpUI();
}

void webUI::update(){

	// Get Web Status
	ESPUI.getControl(fanSwitch)->value.toInt() ? api.turnOnFan() : api.turnOffFan();
	ESPUI.getControl(heatSwitch)->value.toInt() ? api.turnOnHeater() : api.turnOffHeater();
	api.setTemperature(ESPUI.getControl(tempSlider)->value.toFloat());
	//Send periodic updates
		
	ESPUI.updateLabel(tempLabel, String(api.getTemperature()));
	ESPUI.updateLabel(humidLabel, String(api.getHumidity()));

	ESPUI.updateSlider(tempSlider, int(api.getReferenceTemperature()));

	//Simple debug UART interface
	if(Serial.available()) {
		switch(Serial.read()) {
			case 'w': //Print IP details
				Serial.println(WiFi.localIP());
				break;
			case 'W': //Reconnect wifi
				connectWifi();
				break;
			case 'C': //Force a crash (for testing exception decoder)
				#if !defined(ESP32)
					((void (*)())0xf00fdead)();
				#endif
				break;
			default:
				Serial.print('#');
				break;
		}
	}
}


// This is the main function which builds our GUI
void setUpUI() {
	//Turn off verbose debugging
	ESPUI.setVerbosity(Verbosity::Quiet);

	//Make sliders continually report their position as they are being dragged.
	ESPUI.sliderContinuous = true;

	/*
	 * Tab:Dryer Tab
	 * Basic dryer control.
	 *-----------------------------------------------------------------------------------------------------------*/
	auto dryertab = ESPUI.addControl(Tab, "", "Filament Dryer");
	tempLabel = ESPUI.addControl(Label, "Temperature [deg C]", "0", Sunflower, dryertab, generalCallback);
	humidLabel = ESPUI.addControl(Label, "Humidity [%]", "0", Turquoise, dryertab, generalCallback);
	fanSwitch = ESPUI.addControl(Switcher, "Fan Switch", "", Sunflower, dryertab, generalCallback);
	heatSwitch = ESPUI.addControl(Switcher, "Heater Switch", "", Sunflower, dryertab, generalCallback);
	tempSlider = ESPUI.addControl(Slider, "Desired Temperature [deg C]", "60", Emerald, dryertab, generalCallback);

	//Finally, start up the UI. 
	//This should only be called once we are connected to WiFi.
	ESPUI.begin(HOSTNAME);
}

//Most elements in this test UI are assigned this generic callback which prints some
//basic information. Event types are defined in ESPUI.h
void generalCallback(Control *sender, int type) {
	Serial.print("CB: id(");
	Serial.print(sender->id);
	Serial.print(") Type(");
	Serial.print(type);
	Serial.print(") '");
	Serial.print(sender->label);
	Serial.print("' = ");
	Serial.println(sender->value);
}

//Utilities
//
//If you are here just to see examples of how to use ESPUI, you can ignore the following functions
//------------------------------------------------------------------------------------------------
void readStringFromEEPROM(String& buf, int baseaddress, int size) {
	buf.reserve(size);
	for (int i = baseaddress; i < baseaddress+size; i++) {
		char c = EEPROM.read(i);
		buf += c;
		if(!c) break;
	}	
}

void connectWifi() {
	int connect_timeout;
	WiFi.setHostname(HOSTNAME);
	Serial.println("Begin wifi...");

	//Load credentials from EEPROM 
	if(!(FORCE_USE_HOTSPOT)) {

		String stored_ssid = WIFI_SSID;
        String stored_pass = WIFI_PASSWORD;

	
		//Try to connect with stored credentials, fire up an access point if they don't work.
		WiFi.begin(stored_ssid.c_str(), stored_pass.c_str());
		connect_timeout = 28; //7 seconds
		while (WiFi.status() != WL_CONNECTED && connect_timeout > 0) {
			delay(250);
			Serial.print(".");
			connect_timeout--;
		}
	}
	
	if (WiFi.status() == WL_CONNECTED) {
		Serial.println(WiFi.localIP());
		Serial.println("Wifi started");

		if (!MDNS.begin(HOSTNAME)) {
			Serial.println("Error setting up MDNS responder!");
		}
	} else {
		Serial.println("\nCreating access point...");
		WiFi.mode(WIFI_AP);
		WiFi.softAPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
		WiFi.softAP(HOSTNAME);

		connect_timeout = 20;
		do {
			delay(250);
			Serial.print(",");
			connect_timeout--;
		} while(connect_timeout);
	}
}

void enterWifiDetailsCallback(Control *sender, int type) {
	if(type == B_UP) {
		Serial.println("Saving credentials to EPROM...");
		Serial.println(ESPUI.getControl(wifi_ssid_text)->value);
		Serial.println(ESPUI.getControl(wifi_pass_text)->value);
		unsigned int i;
		EEPROM.begin(100);
		for(i = 0; i < ESPUI.getControl(wifi_ssid_text)->value.length(); i++) {
			EEPROM.write(i, ESPUI.getControl(wifi_ssid_text)->value.charAt(i));
			if(i==30) break; //Even though we provided a max length, user input should never be trusted
		}
		EEPROM.write(i, '\0');

		for(i = 0; i < ESPUI.getControl(wifi_pass_text)->value.length(); i++) {
			EEPROM.write(i + 32, ESPUI.getControl(wifi_pass_text)->value.charAt(i));
			if(i==94) break; //Even though we provided a max length, user input should never be trusted
		}
		EEPROM.write(i + 32, '\0');
		EEPROM.end();
	}
}

void textCallback(Control *sender, int type) {
	//This callback is needed to handle the changed values, even though it doesn't do anything itself.
}

void randomString(char *buf, int len) {
	for(auto i = 0; i < len-1; i++) 
		buf[i] = random(0, 26) + 'A';
	buf[len-1] = '\0';
}