# Ejercicio Uno – Análisis con Wireshark

-What is the IP address of the client that initiates the conversation?
a) La dirección IP del cliente que inicia la conversación es 131.247.95.216.

-Use the first two packets to identify the server that is going to be contacted. List the common
name, and three IP addresses that can be used for the server.

b) En las tramas 1 y 2, el cliente realiza una consulta DNS al servidor 131.247.92.200 para resolver <www.google.com>.
El servidor responde con:

Nombre común (CNAME): <www.google.com>

Direcciones IP: 64.233.161.99, 64.233.161.104, 64.233.161.147

-What is happening in frames 3, 4, and 5?
c) En las tramas 3, 4 y 5 se establece el handshake de tres vías de TCP entre el cliente y el servidor (SYN, SYN-ACK, ACK).

-What is happening in frames 6 and 7?
d) En la trama 6, el cliente envía una solicitud HTTP GET para obtener la página principal. En la trama 7, el servidor responde con un ACK TCP, confirmando la recepción de la solicitud, pero aún sin enviar contenido HTTP.

e)Ignore frame eight. However, for your information, frame eight is used to manage flow
control.

-What is happening in frames nine and ten? How are these two frames related?
f) En la trama 9, el cliente envía un ACK para confirmar la recepción de datos anteriores. En la trama 10, el servidor responde con un mensaje HTTP 200 OK y comienza a entregar contenido text solicitado previamente.

-What happens in packet 11?
g) En la trama 11, el cliente envía un acuse de recibo (ACK) para confirmar que recibió los datos del servidor.

-After the initial set of packets is received, the client sends out a new request in packet 12.
This occurs automatically without any action by the user. Why does this occur? See the first
“hint” to the left.
-Hint:: See the accompanying document titled the “QuickStart Guide” – Look under the appendix describing“Hits Versus Page Views”.
h) En la trama 12, el cliente realiza automáticamente una nueva solicitud HTTP para obtener la imagen /intl/en/images/logo.gif. Esto ocurre porque el contenido HTML entregado previamente hace referencia a ese recurso, y el navegador lo solicita por sí solo al procesar la página.

-What is occurring in packets 13 through 22?
i) Entre los paquetes 13 y 22 se produce el intercambio de segmentos TCP y fragmentos de datos HTTP como parte de la entrega del recurso solicitado en la trama 12. No hay una nueva solicitud HTTP aún; se está completando la transmisión anterior.

-Explain what happens in packets 23 through 26. See the second “hint” to the left.
j) En las tramas 23 a 26, el servidor finaliza el envío del archivo favicon.ico, y el cliente responde con los últimos ACKs, cerrando la transacción HTTP.

-In one sentence describe what the user was doing (Reading email? Accessing a web page?
FTP? Other?).
k) El usuario estaba accediendo a una página web (consultando un sitio, cargando HTML, imágenes e íconos).
