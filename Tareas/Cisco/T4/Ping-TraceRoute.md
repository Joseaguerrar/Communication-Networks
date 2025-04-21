# Ping and Traceroute

## Learning Objectives

Upon completion of this lab, you will be able to:

* Use the ping command to verify simple TCP/IP network connectivity
* Use the tracert / traceroute command to verify TCP/IP connectivity

## Introduction

This activity is the Packet Tracer equivalent to Lab 6.7.1: Ping and Traceroute.

## Task 1: Use the ping Command to Verify Simple TCP/IP Network Connectivity

### Step 1. Using PC-1A, Verify Network Layer

Use the command ipconfig at the command prompt to verify TCP/IP Network layer connectivity on the local host computer.

```bash
C:\>ipconfig

Bluetooth Connection:(default port)

   Connection-specific DNS Suffix..: 
   Link-local IPv6 Address.........: ::
   IPv6 Address....................: ::
   IPv4 Address....................: 0.0.0.0
   Subnet Mask.....................: 0.0.0.0
   Default Gateway.................: ::
                                     0.0.0.0

FastEthernet0 Connection:

   Connection-specific DNS Suffix..: 
   Link-local IPv6 Address.........: FE80::201:64FF:FE65:8B74
   IPv6 Address....................: ::
   IPv4 Address....................: 172.16.1.1
   Subnet Mask.....................: 255.255.0.0
   Default Gateway.................: ::
                                     172.16.255.254

```
**R/Tiene IP válida el gateway configurado y una máscara de subred.**

### Step 2. Ping Gateway

Verify TCP/IP Network layer connectivity on the LAN. Enter the command ping 172.16.255.254 to verify TCP/IP Network layer connectivity to the default gateway.

```bash
C:\> ping 172.16.255.254

Pinging 172.16.255.254 with 32 bytes of data:

Reply from 172.16.255.254: bytes=32 time=1ms TTL=255
Reply from 172.16.255.254: bytes=32 time<1ms TTL=255
Reply from 172.16.255.254: bytes=32 time<1ms TTL=255
Reply from 172.16.255.254: bytes=32 time<1ms TTL=255

Ping statistics for 172.16.255.254:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
Approximate round trip times in milli-seconds:
    Minimum = 0ms, Maximum = 1ms, Average = 0ms

```

**R/El host puede comunicarse con su gateway.**

### Step 3. Ping Remote Host

Verify TCP/IP Network layer connectivity to a remote network. Enter the command ping 192.168.254.254 to verify TCP/IP Network layer connectivity to a device on a remote network. In this case the Eagle Server will be used.

```bash
C:\>ping 192.168.254.254

Pinging 192.168.254.254 with 32 bytes of data:

Request timed out.
Reply from 192.168.254.254: bytes=32 time=7ms TTL=126
Reply from 192.168.254.254: bytes=32 time=16ms TTL=126
Reply from 192.168.254.254: bytes=32 time=7ms TTL=126

Ping statistics for 192.168.254.254:
    Packets: Sent = 4, Received = 3, Lost = 1 (25% loss),
Approximate round trip times in milli-seconds:
    Minimum = 7ms, Maximum = 16ms, Average = 10ms

```

**R/Hay conectividad hacia el Eagle Server, aún teniendo 25% de pérdida.**

## Task 2: Use the tracert Command to Verify TCP/IP Connectivity

### Step 1. Verify Hops

Verify TCP/IP Network layer connectivity with the tracert command. Open the command prompt and enter the command tracert 192.168.254.254.

```bash
C:\>tracert 192.168.254.254

Tracing route to 192.168.254.254 over a maximum of 30 hops: 

  1   0 ms      0 ms      0 ms      172.16.255.254
  2   0 ms      3 ms      0 ms      10.10.10.6
  3   0 ms      3 ms      0 ms      192.168.254.254

Trace complete.
```

**Conclusión**

* El paquete llega correctamente al destino en solo 3 saltos.

* Todos los nodos responden rápidamente y no hay pérdida de paquetes en la ruta.

* La red está correctamente configurada y el enrutamiento funciona bien.

## Task 3: Reflection

### Step 1. View Outputs

View the outputs of the traceroute command and compare them to what the command prompt displayed.

#### Qué muestra la salida?
* Muestra todos los nodos (routers) por los que pasan los paquetes.

* Permite ver si hay retrasos o problemas en algún punto del camino.

* En este caso, muestra una ruta clara desde el PC, pasando por el gateway y un router intermedio, hasta llegar al Eagle Server.
