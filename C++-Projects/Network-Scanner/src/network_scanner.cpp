#include "network_scanner.h"
#include <iostream>
#include <sys/socket.h>      // for socket operations
#include <arpa/inet.h>       // for IP address conversions
#include <unistd.h>          // for close() function
#include <netinet/ip_icmp.h> // for ICMP header
#include <chrono>            // for timing
#include <cstring>           // for memset function
#include <vector>            // for std::vector

// Simple ping function using a system call
bool ping(const std::string& ip) {
    // Construct a command to ping the IP address
    // -c 1 sends one packet, -W 1 sets a 1-second timeout, redirect output to /dev/null
    std::string command = "ping -c 1 -W 1 " + ip + " > /dev/null 2>&1";
    // Execute command; if successful, system() returns 0
    return (system(command.c_str()) == 0);
}

// Function ping_sweep to find active IP addresses in a range
std::vector<std::string> ping_sweep(const std::string& ip_range) {
    std::vector<std::string> active_ips; // Vector to store active IPs
    for (int i = 1; i <= 254; ++i) {
        // Generate each IP in the given range by appending to the base range
        std::string ip = ip_range + std::to_string(i);
        // If the ping is successful, add the IP to the list of active addresses
        if (ping(ip)) {
            std::cout << "Active IP: " << ip << std::endl;
            active_ips.push_back(ip);
        }
    }
    return active_ips;
}

// Function port_scan to check open ports on a given IP address
void port_scan(const std::string& ip_address) {
    // Scan ports from 1 to 1024
    for (int port = 1; port <= 1024; ++port) {
        // Create a TCP socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            continue;  // If socket creation fails, skip to the next port
        }

        // Configure the address struct with the IP and port to connect to
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);  // Convert port to network byte order
        inet_pton(AF_INET, ip_address.c_str(), &addr.sin_addr); // Set IP address

        // Try to connect to the IP on the specified port
        if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0) {
            // If connection is successful, the port is open
            std::cout << "Port " << port << " is open on " << ip_address << std::endl;
        }
        // Close the socket after each attempt
        close(sock);
    }
}

