#include "esp_camera.h"
#include <WiFi.h>
#include <ESP32Servo.h>

// Camera model
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// WiFi
const char* ssid = "......";
const char* password = "12345678";

// ================= SERVO =================
Servo myServo;
int servoPos = 90;
int servoPin = 13;
// Function prototype
void startCameraServer();

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  // Servo init
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);    
  myServo.attach(servoPin, 500, 2400); 
  myServo.write(servoPos);    

  // Camera config
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565;

  // (face detection stable)
  config.frame_size = FRAMESIZE_QVGA;
  config.fb_count = 2;

  config.jpeg_quality = 12;

  // Init camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed: 0x%x\n", err);
    return;
  }

  // WiFi connect
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Start server 
  startCameraServer();
}

// ================= LOOP =================
void loop() {
  delay(1000);
}
