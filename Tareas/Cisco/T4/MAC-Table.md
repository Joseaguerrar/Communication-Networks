# Cisco Switch MAC Table Examination

## Addressing Table

This activity does not include an addessing table.

## Learning Objectives

* Use the Telnet protocol to log into a Cisco Switch
* Use the Cisco IOS show mac-address-table command to examine MAC address and port associations

## Introduction

Switches maintain a table of MAC addresses and associated switch port. When a switch receives a frame, the destination MAC address is checked against the table, and the corresponding port is used to route the frame out of the switch. If a switch does not know which port to route the frame, or the frame is a broadcast, then the frame is routed out all ports except the port where it originated. Access to Cisco devices can be accomplished through several means. A console port can be used if the
Cisco router or switch is within the same physical proximity of a computer. Using Packet Tracer's terminal utility, a serial connection can be established. For devices physically distant from the network engineer, network connectivity can be established through two means. If the network is not secure, a modem configured on the AUX port enables telephone access. For secure networks, the Cisco device can be configured for a Telnet session. In this lab, the student will connect to the switch via a Telnet session.

## Task 1: Use the Telnet protocol to log into a Cisco Switch

### Step 1. Access Host PC-PT 1A Command Prompt

Use the Command Prompt button from the Desktop Tab.

### Step 2. Use the Telnet command to access S1-Central

Ping the switch's IP address first to resolve ARP. Then enter the command telnet 172.16.254.1. Packet Tracer does not support user names on switches. When prompt enter cisco as the password.

```bash
C:\>ping 172.16.254.1

Pinging 172.16.254.1 with 32 bytes of data:

Request timed out.
Reply from 172.16.254.1: bytes=32 time<1ms TTL=255
Reply from 172.16.254.1: bytes=32 time<1ms TTL=255
Reply from 172.16.254.1: bytes=32 time<1ms TTL=255

Ping statistics for 172.16.254.1:
    Packets: Sent = 4, Received = 3, Lost = 1 (25% loss),
Approximate round trip times in milli-seconds:
    Minimum = 0ms, Maximum = 0ms, Average = 0ms

C:\>telnet 172.16.254.1
Trying 172.16.254.1 ...Open
 *******************************************************************
                 This is Lab switch S1-Central.
                 Authorized access only.
 *******************************************************************



User Access Verification

Password: 
S1-Central>
```

## Task 2: Use the Cisco IOS show mac-address-table command to examine MAC addresses and port associations

### Step 1. Examine the switch MAC address table

The command show mac-address-table ? will show only the options supported by Packet Tracer.

```bash
S1-Central>show mac-address-table ?
  dynamic     Dynamic entry type
  interfaces  Interface entry type
  static      Static entry type
  <cr>
S1-Central>show mac-address-table 
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----

   1    0001.6465.8b74    DYNAMIC     Fa0/1
```

**En este caso sale la dirección Mac del Host A ya que se hizo ping, dinámico porque se registró cuando se hizo la consulta.**

### Step 2. Examine dynamic MAC address table entries

The command show mac-address-table will show only the entry for the PC from which you accessed the switch. Try using the IOS ping command to ping the router gateway and the other PCs, and then issue the command again.

```bash
S1-Central>ping 172.16.1.2

Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 172.16.1.2, timeout is 2 seconds:
.!!!!
Success rate is 80 percent (4/5), round-trip min/avg/max = 0/0/0 ms

S1-Central>ping 172.16.255.254

Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 172.16.255.254, timeout is 2 seconds:
.!!!!
Success rate is 80 percent (4/5), round-trip min/avg/max = 0/0/0 ms

S1-Central>show mac-address-table
          Mac Address Table
-------------------------------------------

Vlan    Mac Address       Type        Ports
----    -----------       --------    -----

   1    0001.6465.8b74    DYNAMIC     Fa0/1
   1    0006.2aed.9e42    DYNAMIC     Fa0/24
   1    0007.ec78.7d6b    DYNAMIC     Fa0/2
```

**En este caso se les hizo ping a:**

* Host B
* Default gateway

**Dinámico porque se registró cuando se hizo la consulta.**

### Step 3. Examine the switch MAC address table

The command show mac-address-table aging-time is not supported by Packet Tracer.

```bash
S1-Central>show mac-address-table aging-time
                                  ^
% Invalid input detected at '^' marker.
```
