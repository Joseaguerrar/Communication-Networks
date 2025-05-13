# Ejercicio 4 – Conversación de red: Acceso a os.ecci.ucr.ac.cr/ci0121

1. Resolución DNS
Cliente (192.168.100.35) pregunta:

"¿Cuál es la dirección IP del sitio os.ecci.ucr.ac.cr?"

Esto ocurre en los paquetes 58 y 59 como una consulta DNS estándar (protocolo DNS sobre UDP, puerto 53).

Servidor responde:

"La IP de os.ecci.ucr.ac.cr es 163.178.104.62."

Esto se ve en el paquete 60, una respuesta DNS.

2.Inicio de conexión TCP
Cliente (192.168.100.35) dice al servidor (163.178.104.62):

"Quiero iniciar una conexión."
(Este es el paquete 64 con una bandera SYN, que inicia el handshake TCP).

Servidor responde (paquete 65):

"De acuerdo, recibí la petición, aquí están mis parámetros." (SYN-ACK)

Cliente confirma (paquete 66):

"Gracias, empecemos a hablar." (ACK)

Esto completa el 3-way handshake TCP.

3.Negociación TLS (cifrado)
Cliente inicia el cifrado (paquete 67):

"Hola, estas son las versiones TLS y los cifrados que puedo usar."
(Client Hello)

Servidor responde (paquetes 68–71):

"Hola, este es mi certificado y aquí están los parámetros del cifrado."
Incluye:

Server Hello

Certificado TLS

Clave pública y handshake TLS

Cliente acepta (paquete 72):

"Entendido, empecemos a cifrar."

A partir de aquí, todo se cifra (contenido en Application Data).

4.Comunicación segura (HTTPS cifrado)
Ambos lados intercambian datos cifrados usando TLS 1.2 (paquetes 73–80):

"Aquí está la información que necesitas."
(Toda la comunicación va cifrada por seguridad).
