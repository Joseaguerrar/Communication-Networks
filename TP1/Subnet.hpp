// Subnet.hpp

#ifndef SUBNET_HPP
#define SUBNET_HPP

#include <string>
#include <vector>
#include <cstdint>

using namespace std;
struct SubnetRequest
{
    string name;   // Nombre del rango (A, B, etc.)
    int original_hosts; // Hosts solicitados
    int adjusted_hosts; // Hosts necesarios (ajustado a potencia de 2)
};

struct SubnetAssignment
{
    string name;
    int adjusted_hosts;
    string network_address;
    int cidr_mask;
    string broadcast_address;
    string first_usable;
    string last_usable;
};

class SubnetCalculator
{
public:
    SubnetCalculator(const string &base_ip, const string &order);

    void addRequest(const string &name, int hosts);
    void processRequests();
    void printAssignments() const;

private:
    string base_ip;
    string order; // "ascending" o "descending"
    vector<SubnetRequest> requests;
    vector<SubnetAssignment> assignments;

    uint32_t ipToInt(const string &ip) const;
    string intToIp(uint32_t ip) const;
    int calculateCidrMask(int adjusted_hosts) const;
    void sortRequests();
};

#endif // SUBNET_HPP
