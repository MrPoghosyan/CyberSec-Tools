#include "network_scanner.h" // Include the custom header file with function declarations
#include <iostream>          // For input and output operations

int main() {
    // Define the IP range for the network scan
    std::string ip_range = "192.168.1.";  // Set your own IP range prefix
    std::cout << "Starting ping sweep for range " << ip_range << "1-254\n";

    // Find active IPs in the specified range
    std::vector<std::string> active_ips = ping_sweep(ip_range);

    // For each active IP, perform a port scan
    for (const auto& ip : active_ips) {
        std::cout << "Scanning ports for " << ip << std::endl;
        port_scan(ip);  // Scan open ports on the active IP
    }

    return 0;  // Indicate successful program termination
}

