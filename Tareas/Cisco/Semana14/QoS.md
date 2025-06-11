# QoS basic configuration

## Author: Francisco Arroyo

## Learning objectives

-Cable a network according to the topology diagram
-Examine current status of the network

1.Build the network in Cisco Packet Tracer

2.Configure the interfaces on the router as follows:

```bash
ECCIR(config)# interface g0/0/0
ECCIR(config-if)# ip address 192.168.2.1 255.255.255.0
ECCIR(config-if)# no shutdown
ECCIR(config)# interface g0/0/1
ECCIR(config-if)# ip address 192.168.1.1 255.255.255.0
ECCIR(config-if)# no shutdown
```

3.Configure the PC's as follows:

```bash
PC1: IP Address 192.168.1.5 subnet mask 255.255.255.0, gateway 192.168.1.1
PC2: IP Address 192.168.1.6 subnet mask 255.255.255.0, gateway 192.168.1.1
PC3: IP Address 192.168.2.5 subnet mask 255.255.255.0, gateway 192.168.2.1
```

4.Classifying traffic Here we will just classify traffic and not really apply any quality of service actions to it.
We will create a classification for any web traffic coming into R1 on interface g0/0/1.
Type in the following commands: First we need to create the rule that specifies web traffic. We do this by creating an access list looking for any traffic on port 80.

```bash
ECCIR(config)# ip access-list extended WWW_BROWSING_ACL
ECCIR(config-ext-nacl)# permit tcp any any eq 80
```

Next we create a class (WWW_BROWSING_CLASS) and have it match on the access list we just created.

```bash
ECCIR(config-ext-nacl)# class-map WWW_BROWSING_CLASS
ECCIR(config-cmap)# match access-group name WWW_BROWSING_ACL
```

Now create a policy (CLASSIFY_WWW) and have it use the class map we just created.

```bash
ECCIR(config-cmap)# policy-map CLASSIFY_WWW
ECCIR(config-pmap)# class WWW_BROWSING_CLASS
```

Now it must be applied to an interface, in this case we want to classify the traffic coming into g0/0/1.

```bash
ECCIR(config-pmap)# interface GigabitEthernet 0/1
ECCIR(config-if)# service-policy input CLASSIFY_WWW
```

5.Type in the following command:

```bash
ECCIR# show policy-map interface g 0/0/1
```

Analyze the output of this command. How many packets show up in www class?

**En mi caso 7 paquetes fueron clasificados como tráfico web HTTP, puerto 80.**

6.Now click on PC2, click Desktop, select Traffic Generator. Set the parameters:

**Application: HTTP**
**Destination IP address: 192.168.2.5**
**Source IP address: 192.168.1.6**
**Starting source port: 4000**

Click on the Send button below just once. Type in the following command in the router again.

```bash
ECCIR# show policy-map interface g 0/0/1
```

Analyze the output of this command. How many packets show up in www class?

**7 paquetes. El número de paquetes no aumentó más después del envío porque ya habían sido clasificados anteriormente. Si hubieras enviado nuevos, podría haber aumentado.**

7.Marking traffic Now we will give the packets from PC2 a higher priority than the packets coming from PC1. Type in the following commands: First create the rule:

```bash
ECCIR(config)# access-list 110 permit ip host 192.168.1.6 any
ECCIR(config-map)# class-map match-all IMPORTANT
ECCIR(config-cmap)# match access-group 110
```

Then create a policy called SETDSCP and set any packets from the class IMPORTANT set to "ef" which is a higher priority than the default packets usually set to 0.

```bash
ECCIR(config-cmap)# policy-map SETDSCP
ECCIR(config-pmap)#class IMPORTANT
ECCIR(config-pmap-c)# set ip dscp ef
```

Now apply the policy to the interface g0/0/1 where PC2 is attached and on inbound traffic set anything from PC2 to "ef".

```bash
ECCIR(config-pmap-c)# interface g0/0/1
ECCIR(config-if)# service-policy input SETDSCP
ECCIR(config-if)# end
```

Type in the following command in the router again.

```bash
ECCIR# show policy-map interface g 0/0/1
```

Analyze the output of this command. How many packets are marked with dscp ef?

**8 paquetes dscp ef. Estos son los paquetes provenientes de PC2 que fueron marcados con prioridad alta.**

9.Now from PC1, ping PC3. Now run the command

```bash
ECCIR# show policy-map interface giga 0/0/1
```

Did the number of packets marked "ef" increase?

**No. Los paquetes de PC1 no coinciden con la ACL, por lo tanto no fueron marcados con dscp ef.**

10.Now from PC2, ping PC3. Now run the command show policy-map interface g0/0/1.
Did the number of packets marked "ef" increase?

**No. El número de paquetes marcados ef aumentó porque PC2 sí está dentro de la ACL.**
