#ifndef SUBNET_HPP
#define SUBNET_HPP

#include <string>
#include <vector>
#include <cstdint>

// Representa una solicitud de subred
struct SubnetRequest
{
    std::string name;   // Nombre del conjunto (A, B, etc.)
    int original_hosts; // Hosts solicitados
    int adjusted_hosts; // Hosts ajustados (potencia de 2)
};

// Representa la asignación de una subred con todos sus datos
struct SubnetAssignment
{
    std::string name;
    int adjusted_hosts;
    std::string network_address;
    int cidr_mask;
    std::string broadcast_address;
    std::string first_usable;
    std::string last_usable;
};

// Calculadora de subredes que realiza ordenamiento, asignación y presentación
class SubnetCalculator
{
public:
    SubnetCalculator(const std::string &base_ip, const std::string &set_order, const std::string &ip_order);

    void addRequest(const std::string &name, int hosts); // Agrega una solicitud
    void processRequests();                              // Realiza el cálculo y asignación
    void printAssignments() const;                       // Imprime el resultado en tabla

private:
    std::string base_ip;   // IP base de la red
    std::string set_order; // "biggest" o "smallest"
    std::string ip_order;  // "biggest" o "smallest"

    std::vector<SubnetRequest> requests;       // Lista de solicitudes
    std::vector<SubnetAssignment> assignments; // Lista de asignaciones

    uint32_t ipToInt(const std::string &ip) const;   // IP string → entero
    std::string intToIp(uint32_t ip) const;          // Entero → IP string
    int calculateCidrMask(int adjusted_hosts) const; // Cálculo de CIDR
    void sortRequests();                             // Ordena las solicitudes
};

#endif
