#include <Arduino.h>
#include <WiFi.h>
#include <golioth/client.h>
#include <golioth/config.h>
#include <golioth/fw_update.h>
#include <golioth/golioth_debug.h>
#include <golioth/golioth_status.h>
#include <golioth/golioth_sys.h>
#include <golioth/lightdb_state.h>
#include <golioth/log.h>
#include <golioth/ota.h>
#include <golioth/payload_utils.h>
#include <golioth/rpc.h>
#include <golioth/settings.h>
#include <golioth/stream.h>
#include <golioth/zcbor_utils.h>

#define WIFI_SSID       ("SSID")
#define WIFI_PASS       ("PASS")
#define GOLIOTH_PSK_ID  ("PSK ID")
#define GOLIOTH_PSK     ("PSK")

// Tag for logging
#define TAG "hello"

// Counter value to send to Golioth
uint32_t counter = 0;

// Given when we have a connection to Golioth
static SemaphoreHandle_t _connected_sem = NULL;

// Golioth client event handler
static void on_client_event(struct golioth_client *client,
                            enum golioth_client_event event,
                            void *arg)
{
    bool is_connected = (event == GOLIOTH_CLIENT_EVENT_CONNECTED);
    if (is_connected)
    {
        xSemaphoreGive(_connected_sem);
    }
    GLTH_LOGI(TAG, "Golioth client %s", is_connected ? "connected" : "disconnected");
}

void setup() {
  // Begin serial
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  // Initialize WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Connect to Golioth
  golioth_client_config config = {
    .credentials = {
      .psk = {
        .psk_id = GOLIOTH_PSK_ID,
        .psk_id_len = strlen(GOLIOTH_PSK_ID),
        .psk = GOLIOTH_PSK,
        .psk_len = strlen(GOLIOTH_PSK),
      },
    },
  };
  golioth_client *client = golioth_client_create(&config);
  assert(client);

  // Set up the Golioth client event handler
  _connected_sem = xSemaphoreCreateBinary();
  golioth_client_register_event_callback(client, on_client_event, NULL);
  GLTH_LOGW(TAG, "Waiting for connection to Golioth...");
  xSemaphoreTake(_connected_sem, portMAX_DELAY);
 
}

void loop() {
  // Send a hello message every 5 seconds
  GLTH_LOGI(TAG, "Sending hello! %d", counter);
  counter++;
  delay(5000);
}
