# Ejercicio 2 – Análisis con Wireshark

-In the first few packets, the client machine is looking up the common name (cname) of a web site to
find its IP address. What is the cname of this web site? Give two IP addresses for this web site.

a) El nombre común (CNAME) del sitio web es <www.yahoo.akadns.net>. Dos direcciones IP asociadas a este nombre son 216.109.117.106 y 216.109.117.109.

-How many packets/frames does it take to receive the web page (the answer to the first http get
request only)?

b) La solicitud HTTP GET se realiza en el paquete 6. El servidor responde con el contenido de la página en los paquetes 22, 24 y 25. En total, se requieren 3 paquetes para entregar la respuesta completa a la solicitud inicial. El 23 no ya que es un ack del cliente.

-Does this web site use gzip to compress its data for sending? Does it write cookies? In order to
answer these questions, look under the payload for the reassembled packet that represents the web
page. This will be the last packet from question b above. Look to see if it has “Content-Encoding”
set to gzip, and to see if it has a “Set-Cookie” to write a cookie.

c) No, el sitio web no utiliza compresión gzip para enviar los datos, ya que no aparece el encabezado Content-Encoding: gzip. Tampoco escribe cookies, ya que no se observa ningún encabezado Set-Cookie en la respuesta del servidor.

-What is happening in packets 26 and 27? Does every component of a web page have to come from
the same server? See the Hint to the left.

d) En el paquete 26, el cliente realiza una nueva consulta DNS para resolver el dominio us.js2.yimg.com. En el paquete 27, el servidor DNS responde con un CNAME y varias direcciones IP. Esto ocurre porque no todos los componentes de una página web provienen del mismo servidor. Algunos recursos, como imágenes o scripts, pueden estar alojados en otros dominios.

-In packet 37 we see another DNS query, this time for us.i1.yimg.com. Why does the client need to
ask for this IP address? Didn’t we just get this address in packet 26? (This is a trick question;
carefully compare the two common names in packet 26 and 37.)

e) El cliente realiza una nueva consulta DNS en el paquete 37 para el dominio us.i1.yimg.com, aunque ya había consultado us.js2.yimg.com en el paquete 26. Esto ocurre porque, aunque los nombres se parecen, son dominios diferentes, por lo que cada uno requiere su propia resolución DNS.

-In packet 42 we see a HTTP “Get” statement, and in packet 48 a new HTTP “Get” statement. Why
didn’t the system need another DNS request before the second get statement? Click on packet 42 and
look in the middle window. Expand the line titled “Hypertext Transfer Protocol” and read the
“Host:” line. Compare that line to the “Host:” line for packet 48.

f) Ambos paquetes (42 y 48) contienen solicitudes HTTP GET al mismo servidor (us.yimg.com). Como la dirección IP de ese dominio ya se había resuelto previamente, el sistema no necesitó realizar una nueva consulta DNS antes de enviar la segunda solicitud.

-Examine packet 139. It is one segment of a PDU that is reassembled with several other segments in
packet 160. Look at packets 141, 142, and 143. Are these three packets also part of packet 160?
What happens if a set of packets that are supposed to be reassembled do not arrive in a continuous
stream or do not arrive in the proper order?

g) Los paquetes 141 y 142 contienen respuestas HTTP 200 OK separadas, correspondientes a diferentes solicitudes GET. Aunque llegan casi simultáneamente desde la misma IP, no forman parte del mismo contenido reensamblado. Si un conjunto de paquetes que sí deben ser reensamblados no llega completo o ordenado, TCP se encarga de reorganizarlos o solicitar retransmisiones antes de entregar el contenido a la aplicación.

-Return to examine frames 141 and 142. Both of these are graphics (GIF files) from the same source
IP address. How does the client know which graphic to match up to each get statement? Hint: Click
on each and look in the middle window for the heading line that starts with “Transmission Control
Protocol”. What difference do you see in the heading lines for the two files? Return to the original
“Get” statements. Can you see the same difference in the “Get” statements?

h) Aunque los paquetes 141 y 142 contienen respuestas HTTP 200 OK para archivos gráficos (GIFs) enviados desde la misma dirección IP, el cliente puede diferenciarlos porque cada uno fue enviado por una conexión TCP distinta. Esto se puede ver en las cabeceras “Transmission Control Protocol” de ambos paquetes, donde los números de puerto de destino son diferentes 1226 y 1225 respectivamente. Al revisar las solicitudes GET originales, también se observa esta diferencia en los puertos, lo que permite al navegador asociar cada respuesta con la solicitud correcta.
