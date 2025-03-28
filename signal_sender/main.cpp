#include <stdio.h>
#include "pico/stdlib.h"
#include "pico_cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include <string>
#include "cyw43_configport.h"

#define WIFI_SSID "XXXX"
#define WIFI_PASSWORD "XXXXX"
#define SERVER_URL "XXXXX"

void send_signal() {
    int sock;
    struct sockaddr_in server_addr;
    
    // Skapa socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("❌ Kunde inte skapa socket\n");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    inet_aton(XXXXX, &server_addr.sin_addr); 

    // Anslut till server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("❌ Kunde inte ansluta till server\n");
        close(sock);
        return;
    }

    // Skicka data
    std::string message = "GET /api/signal HTTP/1.1\r\nHost: XXXXXX\n";
    send(sock, message.c_str(), message.length(), 0);

    printf("📡 Signal skickad till server!\n");

    // Stäng socket
    close(sock);
}

int main() {
    stdio_init_all();

    // Initiera WiFi
    if (cyw43_arch_init()) {
        printf("❌ WiFi-init misslyckades\n");
        return -1;
    }

    printf("🔄 Ansluter till WiFi...\n");
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_MIXED, 10000)) {
        printf("❌ Kunde inte ansluta till WiFi\n");
        return -1;
    }
    printf("✅ Ansluten till WiFi

