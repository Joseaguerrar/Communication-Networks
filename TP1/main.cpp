#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include "Subnet.hpp"

using namespace std;

// Genera nombres de conjunto estilo A, B, ..., Z, AA, AB, ...
string generarNombre(int index)
{
    string nombre;
    while (index >= 0)
    {
        nombre = char('A' + (index % 26)) + nombre;
        index = index / 26 - 1;
    }
    return nombre;
}

// Procesa el archivo de entrada con formato tipo ejemplo
void procesarEntrada(istream &input)
{
    string line, base_ip, set_order, ip_direction;
    SubnetCalculator *calc = nullptr;

    regex red_regex(R"(Assigned network:\s*(\d+\.\d+\.\d+\.\d+))");
    regex set_regex(R"(Set:\s*(biggest|smallest))", regex::icase);
    regex ip_regex(R"(IP:\s*(biggest|smallest))", regex::icase);
    regex solicitud_regex(R"((\d+)\s+addresses\s+for\s+range\s+([A-Z]+))");

    while (getline(input, line))
    {
        smatch match;

        if (regex_search(line, match, red_regex))
        {
            base_ip = match[1];
        }
        else if (regex_search(line, match, set_regex))
        {
            set_order = match[1];
        }
        else if (regex_search(line, match, ip_regex))
        {
            ip_direction = match[1];
        }
        else if (regex_search(line, match, solicitud_regex))
        {
            if (!calc)
            {
                if (base_ip.empty() || set_order.empty() || ip_direction.empty())
                {
                    cerr << "Faltan parámetros (Assigned network, Set o IP)." << endl;
                    return;
                }
                calc = new SubnetCalculator(base_ip, set_order, ip_direction);
            }
            int cantidad = stoi(match[1]);
            string nombre = match[2];
            calc->addRequest(nombre, cantidad);
        }
    }

    if (calc)
    {
        calc->processRequests();
        calc->printAssignments();
        delete calc;
    }
    else
    {
        cerr << "No se encontraron solicitudes válidas." << endl;
    }
}

// Punto de entrada principal
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        ifstream archivo(argv[1]);
        if (!archivo)
        {
            cerr << "No se pudo abrir el archivo: " << argv[1] << endl;
            return 1;
        }
        procesarEntrada(archivo);
    }
    else
    {
        // Modo interactivo
        string base_ip, set_order, ip_order;
        cout << "=== Subnet Calculator (modo interactivo) ===" << endl;

        cout << "Ingrese la red base (ej. 192.168.0.0): ";
        getline(cin, base_ip);

        cout << "Orden de conjuntos (biggest/smallest): ";
        getline(cin, set_order);

        cout << "Orden de IPs (biggest/smallest): ";
        getline(cin, ip_order);

        SubnetCalculator calc(base_ip, set_order, ip_order);

        cout << "Ingrese las cantidades de hosts requeridos (uno por línea)." << endl;
        cout << "Presione Enter sin escribir nada para finalizar." << endl;

        int index = 0;
        string linea;
        while (true)
        {
            cout << "Cantidad de hosts #" << (index + 1) << ": ";
            getline(cin, linea);
            if (linea.empty())
                break;

            try
            {
                int hosts = stoi(linea);
                string nombre = generarNombre(index);
                calc.addRequest(nombre, hosts);
                index++;
            }
            catch (const invalid_argument &)
            {
                cerr << "Entrada inválida. Ingrese un número válido." << endl;
            }
        }

        cout << endl
             << "Procesando..." << endl
             << endl;
        calc.processRequests();
        calc.printAssignments();
    }

    return 0;
}
