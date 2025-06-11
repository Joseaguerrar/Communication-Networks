# Packet Tracer - TCP and UDP Communications

## Objectives

-Part 1: Generate Network Traffic in Simulation Mode

-Part 2: Examine the Functionality of the TCP and UDP Protocols

### Background

This simulation activity is intended to provide a foundation for understanding TCP and UDP in detail. Packet Tracer simulation mode provides you the ability to view the state of different PDUs as they travel through the network.

Packet Tracer Simulation mode enables you to view each of the protocols and the associated PDUs. The steps outlined below lead you through the process of requesting network services using various applications that are available on a client PC. You will explore the functionality of the TCP and UDP protocols, multiplexing, and the function of port numbers in determining which local application requested the data or is sending the data. Packet Tracer will not score this activity.

## Instructions

### Part 1: Generate Network Traffic in Simulation Mode and View Multiplexing

#### Step 1: Generate traffic to populate Address Resolution Protocol (ARP) tables

Perform the following task to reduce the amount of network traffic viewed in the simulation.

-a.     Click MultiServer and click the Desktop tab > Command Prompt.

-b.     Enter the ping -n 1 192.168.1.255 command. You are pinging the broadcast address for the client LAN. The command option will send only one ping request rather than the usual four. This will take a few seconds as every device on the network responds to the ping request from MultiServer.

-c.     Close the MultiServer window.

#### Step 2: Generate web (HTTP) traffic

-a.     Switch to Simulation mode.

-b.     Click HTTP Client and open the Web Browser from the desktop.

-c.     In the URL field, enter 192.168.1.254 and click Go. Envelopes (PDUs) will appear in the topology window.

-d.     Minimize, but do not close, the HTTP Client configuration window.

#### Step 3: Generate FTP traffic

-a.     Click FTP Client and open the Command Prompt from the desktop

-b.     Enter the ftp 192.168.1.254 command. PDUs will appear in the simulation window.

-c.     Minimize, but do not close, the FTP Client configuration window.

#### Step 4: Generate DNS traffic

-a.     Click DNS Client and open the Command Prompt.

-b.     Enter the nslookup multiserver.pt.ptu command. A PDU will appear in the simulation window.

-c.     Minimize, but do not close, the DNS Client configuration window.

#### Step 5: Generate Email traffic

-a.     Click E-Mail Client and open the E Mail tool from the Desktop.

-b.     Click Compose and enter the following information:

        1) To: <user@multiserver.pt.ptu>

        2) Subject: personalize the subject line

        3) E-Mail Body: personalize the Email

-c.     Click Send.

-d.     Minimize, but do not close, the E-Mail Client configuration window.

#### Step 6: Verify that the traffic is generated and ready for simulation

There should now be PDU entries in the simulation panel for each of the client computers.

#### Step 7: Examine multiplexing as the traffic crosses the network

You will now use the Capture/Forward button in the Simulation Panel to observe the different protocols travelling on the network.

>Note: The Capture/Forward button ‘ >| ‘ is a small arrow pointing to the right with a vertical bar next to it.

-a.     Click Capture/Forward once. All of the PDUs travel to the switch.

-b.     Click Capture/Forward six times and watch the PDUs from the different hosts as they travel on the network. Note that only one PDU can cross a wire in each direction at any given time.

**Questions:**

What is this called?

>A esto se le llama multiplexación, proceso donde múltiples señales o flujos de datos comparten un mismo medio físico. En redes, permite que múltiples aplicaciones (como HTTP, FTP, DNS, etc.) compartan una sola conexión física al usar diferentes números de puerto.

A variety of PDUs appears in the event list in the Simulation Panel. What is the meaning of the different colors?

**Cada color en las PDUs representa un protocolo diferente. Por ejemplo:**

**Verde: ARP**

**Naranja: HTTP**

**Rojo: TCP**

**Azul: DNS**

**Morado: FTP**

**Rosado: SMTP o POP3**

**Esto permite distinguir visualmente qué tipo de tráfico se está observando en la simulación.**

### Part 2: Examine Functionality of the TCP and UDP Protocols

#### Step 1: Examine HTTP traffic as the clients communicate with the server

-a.     Click Reset Simulation.

-b.     Filter the traffic that is currently displayed to only HTTP and TCP PDUs. To filter the traffic that is currently displayed:

        1) Click Edit Filters and toggle the Show All/None button.

        2) Select HTTP and TCP. Click the red “x” in the upper right-hand corner of the Edit Filters box to close it. Visible Events should now display only HTTP and TCP PDUs.

-c.     Open the browser on HTTP Client and enter 192.168.1.254 in the URL field. Click Go to connect to the server over HTTP. Minimize the HTTP Client window.

-d.     Click Capture/Forward until you see a PDU appear for HTTP. Note that the color of the envelope in the topology window matches the color code for the HTTP PDU in the Simulation Panel.

**Question:**
Why did it take so long for the HTTP PDU to appear?

**Porque antes de que pueda comenzar la transferencia HTTP, TCP debe establecer una conexión usando el three-way handshake: SYN → SYN-ACK → ACK. Solo después de eso se puede enviar el PDU HTTP real.**

-e.     Click the PDU envelope to show the PDU details. Click the Outbound PDU Details tab and scroll down to the second to the last section.

**Questions:**
What is the section labeled?

**Se llama TCP. Es la sección que describe los detalles del protocolo de transporte.**

Are these communications considered to be reliable?

**Sí. TCP es un protocolo orientado a la conexión y confiable, ya que asegura la entrega de los datos mediante confirmaciones, control de errores y retransmisiones si es necesario.**

Record the SRC PORT, DEST PORT, SEQUENCE NUM, and ACK NUM values.

-f.      Look at the value in the Flags field, which is located next to the Window field. The values to the right of the “b” represent the TCP flags that are set for this stage of the data conversation. Each of the six places corresponds to a flag. The presence of a “1” in any place indicates that the flag is set. More than one flag can be set at a time. The values for the flags are shown below.

| Flag Place | 6   | 5   | 4   | 3   | 2   | 1   |
|------------|-----|-----|-----|-----|-----|-----|
| Value      | URG | ACK | PSH | RST | SYN | FIN |

**Question:**
Which TCP flags are set in this PDU?

**La flag de SYN ya que estamos iniciando una conexión TCP.**

-g.     Close the PDU and click Capture/Forward until a PDU with a checkmark returns to the HTTP Client.

-h.     Click the PDU envelope and select Inbound PDU Details.

**Question:**
How are the port and sequence numbers different than before?

**Los puertos están invertidos porque ahora es el servidor quien responde.**

**El SEQUENCE NUM es 0, ya que el servidor empieza su propia secuencia.**

**El ACK NUM es 1, reconociendo el SYN del cliente.**

**El Flags muestra SYN + ACK (0b00010010), indicando que el servidor acepta la conexión y responde.**

-i.      Click the HTTP PDU which HTTP Client has prepared to send to MultiServer. This is the beginning of the HTTP communication. Click this second PDU envelope and select Outbound PDU Details.

**Question:**
What information is now listed in the TCP section? How are the port and sequence numbers different from the previous two PDUs?

**Puerto 1026, destino puerto 80, secuencia 1, ACK 1.**

-j.      Reset the simulation.

#### Step 2: Examine FTP traffic as the clients communicate with the server

-a.     Open the command prompt on the FTP Client desktop. Initiate an FTP connection by entering ftp 192.168.1.254.

-b.     In the Simulation Panel, change Edit Filters to display only FTP and TCP.

-c.     Click Capture/Forward. Click the second PDU envelope to open it.

Click the Outbound PDU Details tab and scroll down to the TCP section.

**Question:**
Are these communications considered to be reliable?

**Sí. El tráfico FTP utiliza TCP, que es un protocolo orientado a la conexión y confiable. Usa números de secuencia, confirmaciones (ACK), y mecanismos de control de errores para garantizar que los datos lleguen correctamente.**

-d.     Record the SRC PORT, DEST PORT, SEQUENCE NUM, and ACK NUM values.

**Question:**
What is the value in the flag field?
**FLAGS: 0b00000010, Solo SYN activado**

-e.     Close the PDU and click Capture/Forward until a PDU returns to the FTP Client with a checkmark.

-f.      Click the PDU envelope and select Inbound PDU Details.

**Question:**
How are the port and sequence numbers different than before?

-g.     Click the Outbound PDU Details tab.

**Question:**
How are the port and sequence numbers different from the previous results?

**Los puertos están invertidos, ya que el tráfico ahora viene del servidor. SEQUENCE NUM inicia desde 0 (servidor). ACK NUM = 1, confirmando que recibió el SYN del cliente. Las banderas TCP activadas son SYN y ACK (0b00010010).**
-h.     Close the PDU and click Capture/Forward until a second PDU returns to the FTP Client. The PDU is a different color.

-i.      Open the PDU and select Inbound PDU Details. Scroll down past the TCP section.

**Question:**
What is the message from the server?

**Welcome to PT Ftp server.**

-j.      Click Reset Simulation.

### Step 3: Examine DNS traffic as the clients communicate with the server

-a.     Repeat the steps in Part 1 to create DNS traffic.

-b.     In the Simulation Panel, change Edit Filters to display only DNS and UDP.

-c.     Click the PDU envelope to open it.

-d.     Look at the OSI Model details for the outbound PDU.

**Question:**
What is the Layer 4 protocol?

**UDP(User Datagram Protocol)**

Are these communications considered to be reliable?

**No, UDP es un protocolo no orientado a la conexión, lo que significa que: No garantiza la entrega. No hay confirmaciones ni reenvíos. Es más rápido, pero menos confiable que TCP.**

-e.     Open the Outbound PDU Details tab and find the UDP section of the PDU formats. Record the SRC PORT and DEST PORT values.

**Source port 1025, destino puerto 53.**

**Question:**
Why are there no sequence and acknowledgement numbers?

**Porque UDP no tiene control de flujo ni confiabiliadad, así que no establece conexión previa, no hay seguimiento de paquetes, por eso no existen campos de sequence o ack en UDP.**

-f.      Close the PDU and click Capture/Forward until a PDU with a check mark returns to the DNS Client.

-g.     Click the PDU envelope and select Inbound PDU Details.

**Question:**
How are the port and sequence numbers different than before?

**Están al reves ya que el tráfico viene del servidor.**

What is the last section of the PDU called? What is the IP address for the name multiserver.pt.ptu?

**La última sección del PDU es DNS answer, y la dirección IP del servidor es 192.168.1.254.**

-h.     Click Reset Simulation.

### Step 4: Examine email traffic as the clients communicate with the server

-a.     Repeat the steps in Part 1 to send an email to <user@multiserver.pt.ptu>.

-b.     In the Simulation Panel, change Edit Filters to display only POP3, SMTP and TCP.

-c.     Click the first PDU envelope to open it.

-d.     Click the Outbound PDU Details tab and scroll down to the last section.

**Questions:**
What transport layer protocol does email traffic use?
**TCP, ambos protocolos SMTP y POP3 se ejecutan sobre TCP para garantizar la entrega confiable del correo**

Are these communications considered to be reliable?

**Sí, TCP es un protocolo confiable y orientado a la conexión, por lo que garantiza la entrega, orden correcto y retransmisión si es necesario.**

-e.     Record the SRC PORT, DEST PORT, SEQUENCE NUM, and ACK NUM values. What is the flag field value?
**Flags: 0b00000010, Solo SYN activado**

-f.      Close the PDU and click Capture/Forward until a PDU returns to the E-Mail Client with a checkmark.

-g.     Click the TCP PDU envelope and select Inbound PDU Details.

**Question:**
How are the port and sequence numbers different than before?
**Los puertos están invertidos, el SEQUENCE NUM es 0 (inicia secuencia desde el servidor), el ACK NUM es 1 (confirma el SYN del cliente), el campo Flags es 0b00010010 → SYN + ACK, indicando el segundo paso del handshake.**

-h.     Click the Outbound PDU Details tab.

**Question:**
How are the port and sequence numbers different from the previous two results?

**En este paquete enviado por el cliente, el puerto de origen sigue siendo 1025 y el puerto de destino 25, igual que en el primer paquete, pero el número de secuencia ahora es 1 en lugar de 0, el número de ack es 1 porque confirma el SYN del servidor, y la única bandera activa es ACK, lo que indica que se está completando el three-way handshake.**

-i.      There is a second PDU of a different color that E-Mail Client has prepared to send to MultiServer. This is the beginning of the email communication. Click this second PDU envelope and select Outbound PDU Details.

**Questions:**
How are the port and sequence numbers different from the previous two PDUs?

**En este paquete enviado por el cliente, el puerto de origen sigue siendo 1025 y el de destino 25, como antes, pero el número de secuencia ahora es mayor porque ya se han intercambiado los SYN y ACK, el número de acuse es 1 porque aún está confirmando la secuencia inicial del servidor, y este paquete ya incluye datos SMTP, por lo que representa el inicio real de la comunicación de aplicación.**

What email protocol is associated with TCP port 25? What protocol is associated with TCP port 110?

**El puerto TCP 25 está asociado al protocolo SMTP (Simple Mail Transfer Protocol), que se usa para enviar correos electrónicos, mientras que el puerto TCP 110 está asociado al protocolo POP3 (Post Office Protocol versión 3), que se usa para recibir correos electrónicos desde el servidor al cliente.**
