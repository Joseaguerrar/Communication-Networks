# Examining a Device's Gateway

## Learning Objectives

* Understand and explain the purpose of a gateway address
* Understand how network information is configured on a Windows computer
* Troubleshoot a hidden gateway address problem

## Introduction

An IP address is composed of a network portion and a host portion. A computer that communicates with another device must first know how to reach the device. For devices on the same local area network (LAN), the host portion of the IP address is used as the identifier. The network portion of the destination device is the same as the network portion of the host device.

However, devices on different networks have different source and destination network numbers. The network portion of the IP address is used to identify when a packet must be sent to a gateway address, which is assigned to a network device that forwards packets between distant networks.

A router is assigned the gateway address for all the devices on the LAN. One purpose of a router is to serve as an entry point for packets coming into the network and exit point for packets leaving the network.

Gateway addresses are very important to users. Cisco estimates that 80 percent of network traffic will be destined to devices on other networks, and only 20 percent of network traffic will go to local devices. This is called the 80/20 rule. Therefore, if a gateway cannot be reached by the LAN devices, users will not be able to perform their job.

## Task 1: Understand and Explain the Purpose of a Gateway Address

Step 1. Open a command prompt window on a pod host computer.
Issue the ipconfig command.

What is the default gateway address?
Default Gateway . . . . . . . . . : 172.16.255.254

Step 2. Use the ping command to verify connectivity with IP address 127.0.0.1.
Was the ping successful?

```bash
C:\>ping 127.0.0.1

Pinging 127.0.0.1 with 32 bytes of data:

Reply from 127.0.0.1: bytes=32 time<1ms TTL=128
Reply from 127.0.0.1: bytes=32 time=5ms TTL=128
Reply from 127.0.0.1: bytes=32 time<1ms TTL=128
Reply from 127.0.0.1: bytes=32 time=5ms TTL=128

Ping statistics for 127.0.0.1:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
Approximate round trip times in milli-seconds:
    Minimum = 0ms, Maximum = 5ms, Average = 2ms
```

 **R/ Sí, la conexión fue exitosa.**

Step 3. Use the ping command to ping different IP addresses on the 127.0.0.0 network, 127.10.1.1, and 127.255.255.255.

Were responses successful? If not, why?

R/ Sí fuerons exitosas, las respuestas fueron similares a las de la pTask 1: Understand and Explain the Purpose of a Gateway Address.rimera prueba.

## Task 2: Understand how Network Information is Configured

Many times connectivity issues are attributed to wrong network settings. In troubleshooting connectivity issues, several tools are available to quickly determine the network configuration.
Step 1. Examine network IP address properties:

By Clicking on the PC > Desktop Tab> IP Configuration
Step 2. To examine network properties using the ipconfig command:

Click on the PC > Desktop Tab > Command Prompt
Then type ipconfig or ipconfig /all

```bash
C:\>ipconfig /all

FastEthernet0 Connection:(default port)

   Connection-specific DNS Suffix..:
   Physical Address................: 0001.6465.8B74
   Link-local IPv6 Address.........: FE80::201:64FF:FE65:8B74
   IPv6 Address....................: ::
   **IPv4 Address....................: 172.16.1.1**
   **Subnet Mask.....................: 255.255.255.0**
   **Default Gateway.................: 172.16.255.254**
                                     172.16.255.254
   DHCP Servers....................: 0.0.0.0
   DHCPv6 IAID.....................:
   DHCPv6 Client DUID..............: 00-01-00-01-09-10-05-C8-00-01-64-65-8B-74
   DNS Servers.....................: ::
                                     192.168.254.254

Bluetooth Connection:

   Connection-specific DNS Suffix..:
   Physical Address................: 00E0.F964.53E8
   Link-local IPv6 Address.........: ::
 --More--
```

**Las líneas en negrita son las mismas que salen en la interfaz del step 1, así son las dos maneras de ver la misma información.**

## Task 3: Troubleshoot a Hidden Gateway Address Problem

When troubleshooting network issues, a thorough understanding of the network can often assist in identifying the real problem.

As the 3rd shift help desk Cisco engineer, you are asked for assistance from the help desk technician. The technician received a trouble ticket from a user on computer host-1A, complaining that computer host-11B, host-11B.example.com, does not respond to pings. The technician verified the cables and network settings on both computers, but nothing unusual was found. You check with the corporate network engineer, who reports that R2-Central has been temporarily brought down for a hardware upgrade. Nodding your head in understanding, you ask the technician to ping the IP address for host-11B, 172.16.11.2 from host-1A. The pings are successful. Then, you ask the technician to ping the gateway IP address, 172.16.254.254, and the pings fail.

Your task is to find and fix the problem that is occurring within this network.

HINT: In Order to Solve This Problem, Check R2-Central's Interfaces

## Solución

Desde Host 1A se pudo hacer ping a 172.16.11.2 (host-11B), pero fallaba el ping al gateway 172.16.255.254.

Se accedió a R2-Central y se ejecutó:

```bash
show ip interface brief
```

Mostrando:

```bash
FastEthernet0/0  172.16.255.254  YES manual  administratively down  down
```

Se activó la interfaz con los comandos:

```bash
configure terminal
interface fa0/0
no shutdown
```

Luego se verificó de nuevo:

```bash
FastEthernet0/0  172.16.255.254  YES manual  up  up
```

Finalmente, desde Host 1A:

```bash
ping 172.16.255.254
```

Resultado:

```bash
Reply from 172.16.255.254: bytes=32 time<1ms TTL=255
...
Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
```

### Conclusión

Se resolvió el problema de conectividad reactivando la interfaz Fa0/0 del router R2-Central. Esto permitió a los hosts comunicarse correctamente con su gateway, completando exitosamente la actividad con un Completion Rate del 100%.
