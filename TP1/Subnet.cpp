#include "Subnet.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

SubnetCalculator::SubnetCalculator(const string &base_ip, const string &set_order, const string &ip_order)
    : base_ip(base_ip), set_order(set_order), ip_order(ip_order) {}

// Agrega una solicitud con ajuste al siguiente múltiplo de potencia de 2
void SubnetCalculator::addRequest(const string &name, int hosts)
{
    int adjusted = 1;
    while (adjusted - 2 < hosts)
    {
        adjusted *= 2;
    }
    requests.push_back({name, hosts, adjusted});
}

// Convierte una IP en string a entero de 32 bits
uint32_t SubnetCalculator::ipToInt(const string &ip) const
{
    istringstream iss(ip);
    uint32_t result = 0;
    string token;
    for (int i = 0; i < 4; ++i)
    {
        getline(iss, token, '.');
        result = (result << 8) | stoi(token);
    }
    return result;
}

// Convierte una IP en entero a string
string SubnetCalculator::intToIp(uint32_t ip) const
{
    ostringstream oss;
    for (int i = 3; i >= 0; --i)
    {
        oss << ((ip >> (i * 8)) & 0xFF);
        if (i != 0)
            oss << '.';
    }
    return oss.str();
}

// Calcula el CIDR correspondiente al tamaño ajustado
int SubnetCalculator::calculateCidrMask(int adjusted_hosts) const
{
    int bits = 0;
    while ((1 << bits) < adjusted_hosts)
        ++bits;
    return 32 - bits;
}

// Ordena las solicitudes según el parámetro de ordenamiento
void SubnetCalculator::sortRequests()
{
    sort(requests.begin(), requests.end(), [&](const SubnetRequest &a, const SubnetRequest &b)
         { return (set_order == "smallest") ? (a.adjusted_hosts < b.adjusted_hosts)
                                            : (a.adjusted_hosts > b.adjusted_hosts); });
}

// Asigna las subredes ya ordenadas según el criterio de IP y tamaño de conjunto
void SubnetCalculator::processRequests()
{
    // Ajuste de hosts a potencias de 2 (para incluir red y broadcast)
    for (auto &r : requests)
    {
        int ajuste = 1;
        while (ajuste - 2 < r.original_hosts)
        {
            ajuste <<= 1;
        }
        r.adjusted_hosts = ajuste;
    }

    // Ordenar por tamaño de conjunto, según "Set: biggest" o "Set: smallest"
    if (set_order == "biggest")
    {
        sort(requests.begin(), requests.end(), [](const SubnetRequest &a, const SubnetRequest &b)
             {
                 if (a.adjusted_hosts == b.adjusted_hosts)
                     return a.name < b.name; // desempatar por nombre
                 return a.adjusted_hosts > b.adjusted_hosts; });
    }
    else
    {
        sort(requests.begin(), requests.end(), [](const SubnetRequest &a, const SubnetRequest &b)
             {
                 if (a.adjusted_hosts == b.adjusted_hosts)
                     return a.name < b.name; // desempatar por nombre
                 return a.adjusted_hosts < b.adjusted_hosts; });
    }

    // Calcular IP de inicio
    uint32_t start_ip = ipToInt(base_ip);
    uint32_t current_ip;

    if (ip_order == "biggest")
    {
        // Obtener la cantidad total de hosts necesarios
        uint32_t total_hosts = 0;
        for (const auto &r : requests)
        {
            total_hosts += r.adjusted_hosts;
        }

        // Calcular la máscara mínima que puede cubrir todos los bloques
        int total_cidr = calculateCidrMask(total_hosts);
        uint32_t block_size = 1u << (32 - total_cidr);

        // Determinar la IP final del bloque completo desde base
        uint32_t end_ip = start_ip + block_size - 1;

        // Comenzar desde la IP final hacia abajo
        current_ip = end_ip;
    }
    else
    {
        // Comenzar desde la base hacia arriba
        current_ip = start_ip;
    }

    // Asignar cada subred con base en current_ip
    for (const auto &r : requests)
    {
        int cidr = calculateCidrMask(r.adjusted_hosts);
        uint32_t block_size = 1u << (32 - cidr);

        uint32_t net_ip, first_ip, last_ip, bc_ip;

        if (ip_order == "biggest")
        {
            // Restar el bloque para encontrar el inicio de red
            net_ip = (current_ip + 1 - block_size) & (~(block_size - 1));
            bc_ip = net_ip + block_size - 1;
            first_ip = net_ip + 1;
            last_ip = bc_ip - 1;

            // Actualizar el current_ip para el siguiente bloque (más abajo)
            current_ip = net_ip - 1;
        }
        else
        {
            // Alinear hacia adelante desde current_ip
            net_ip = current_ip & (~(block_size - 1));
            bc_ip = net_ip + block_size - 1;
            first_ip = net_ip + 1;
            last_ip = bc_ip - 1;

            // Avanzar al siguiente bloque
            current_ip = bc_ip + 1;
        }

        // Guardar la asignación
        assignments.push_back({r.name,
                               r.adjusted_hosts,
                               intToIp(net_ip),
                               cidr,
                               intToIp(bc_ip),
                               intToIp(first_ip),
                               intToIp(last_ip)});
    }
}

// Imprime las asignaciones con formato de tabla usando '|'
void SubnetCalculator::printAssignments() const
{
    cout << left << setw(6) << "Set" << " | "
         << setw(8) << "N" << " | "
         << setw(18) << "Net" << " | "
         << setw(6) << "Mask" << " | "
         << setw(18) << "BC" << " | "
         << setw(18) << "First" << " | "
         << setw(18) << "Last" << endl;

    cout << string(6 + 3 + 8 + 3 + 18 + 3 + 6 + 3 + 18 + 3 + 18 + 3 + 18, '-') << endl;

    for (const auto &a : assignments)
    {
        cout << left << setw(6) << a.name << " | "
             << setw(8) << a.adjusted_hosts << " | "
             << setw(18) << a.network_address << " | "
             << setw(6) << a.cidr_mask << " | "
             << setw(18) << a.broadcast_address << " | "
             << setw(18) << a.first_usable << " | "
             << setw(18) << a.last_usable << endl;
    }
}
