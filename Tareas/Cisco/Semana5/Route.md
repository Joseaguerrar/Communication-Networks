# Examining a Route

## Addressing Table

This activity does not include an addressing table.

## Learning Objectives

Use the route command to view a PT-PC routing table
Use the command command prompt to telnet and connect to a Cisco router
Examine router routes using basic Cisco IOS commands

## Introduction

For packets to travel across a network, a device must know the route to the destination network. This lab will compare how routes are used in Windows computers and the Cisco router. Some routes are added to routing tables automatically, based upon configuration information on the network interface. The device considers a network directly connected when it has an IP address and network mask configured, and the network route is automatically entered into the routing table. For networks that are not directly connected, a default gateway IP address is configured that will send traffic to a device that should know about the network.

### Task 1: View the Routing Table

#### Step 1. Access the command prompt

Click on a PC> Desktop Tab> Command Prompt

#### Step 2. Type netstat -r to view the current routing table

NOTE: Packet Tracer 4.1 does not support the ROUTE commands that would allow you examine the active routes on a PC.  Unlike the netstat –r command, the route command can be used to view, add, delete, or change routing table entries.


```bash
C:\>netstat -r

Route Table
===========================================================================
Interface List
0x1 ........................... PT TCP Loopback interface
0x2 ...00 16 6f 0d 88 ec ...... PT Bluetooth interface
0x1 ........................... PT TCP Loopback interface
0x2 ...00 16 6f 0d 88 ec ...... PT Ethernet interface
===========================================================================
===========================================================================
Active Routes:
Network Destination        Netmask          Gateway       Interface  Metric
          0.0.0.0          0.0.0.0   172.16.255.254      172.16.1.1       1
Default Gateway:      172.16.255.254
===========================================================================
Persistent Routes:
  None
```

### Task 2: Use the Command Prompt to Telnet and Connect to a Router

#### Step 1. Using the Command prompt as a Telnet client

Open the command prompt window by clicking on a PC > Desktop Tab> Command Prompt.  Next, type the command telnet followed by the IP address of the default gateway of the remote router (172.16.255.254).  The username required is ccna1, and the password is cisco.
NOTE: You will NOT see the password while you type.


```bash
C:\>telnet 172.16.255.254
Trying 172.16.255.254 ...Open
*****************************************************************
                This is Eagle 1 lab router R2-Central.
                Authorized access only.
*****************************************************************



User Access Verification

Username: ccna1
Password: 
R2-Central>
```

### Task 3: Examine Router Routes using Basic Cisco IOS Commands

#### Step 1. Explore privileged mode

Once logged into the remote router, type enable to enter privileged mode. The required password here is class. Once again you will not see the password while you type.

```bash
R2-Central>enable
Password: 
```

#### Step 2. Enter the command to display the router routing table

Use the show ip route command, to display a  much more detailed routing table then on a host computer. This is to be expected, because the job of a router is to route traffic between networks.

```bash
R2-Central# show ip route
Codes: C - connected, S - static, I - IGRP, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2, E - EGP
       i - IS-IS, L1 - IS-IS level-1, L2 - IS-IS level-2, ia - IS-IS inter area
       * - candidate default, U - per-user static route, o - ODR
       P - periodic downloaded static route

Gateway of last resort is 10.10.10.6 to network 0.0.0.0

     10.0.0.0/30 is subnetted, 1 subnets
C       10.10.10.4 is directly connected, Serial0/0/0
C    172.16.0.0/16 is directly connected, FastEthernet0/0
S*   0.0.0.0/0 [1/0] via 10.10.10.6
```

How is IP mask information displayed in a router routing table?

Todas las rutas mostradas en la tabla de enrutamiento del router Cisco tienen una máscara de subred asociada, aunque **no siempre se muestra explícitamente en cada línea**. La información de máscara se representa en **formato CIDR**, donde:

**¿Qué hace CIDR?**
CIDR permite asignar máscaras de subred más flexibles, usando una notación como /X, en lugar de obligar a usar solo:

* Clase A → 255.0.0.0

* Clase B → 255.255.0.0

* Clase C → 255.255.255.0

Ahora, con CIDR, por ejemplo:

* /30 → para enlaces punto a punto

* /27 → para subredes pequeñas

* /16 → para redes grandes

####  Explicación

- `172.16.0.0/16`: red local conectada directamente con máscara `255.255.0.0`

- `10.10.10.4`: está dentro del bloque `10.0.0.0/30`, y **hereda** su máscara `/30` (equivale a `255.255.255.252`) 

- `0.0.0.0/0`: es la ruta por defecto, que significa "cualquier destino"

Aunque algunas entradas no repiten la máscara (`/30`) en cada línea, el router las agrupa con encabezados como `is subnetted` para mantener la salida más ordenada.
