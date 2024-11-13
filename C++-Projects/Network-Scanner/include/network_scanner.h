// include/network_scanner.h
#ifndef NETWORK_SCANNER_H
#define NETWORK_SCANNER_H

#include <string>
#include <vector>

std::vector<std::string> ping_sweep(const std::string& ip_range);
void port_scan(const std::string& ip_address);

#endif // NETWORK_SCANNER_H
