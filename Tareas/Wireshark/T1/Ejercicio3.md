# Ejercicio 3 – Análisis con Wireshark

-Compare the destination port in the TCP packet in frame 3 with the destination port in the TCP
packet in frame 12. What difference do you see? What does this tell you about the difference in the
two requests?

a)El paquete TCP en el frame 3 tiene como puerto de destino el 80, que corresponde al protocolo HTTP (sin cifrado). Por otro lado el paquete TCP en el frame 12 tiene como puerto de destino el 443, que corresponde al protocolo HTTPS (con cifrado TLS/SSL). Esto indica que la solicitud a <www.yahoo.com> se hace sin cifrado, mientras que la de my.usf.edu se realiza de forma segura usando TLS.

-Explain what is happening in row “iii” above. Why are there no frames listed for yahoo in row “iii"?

b)En la fila iii) (frames 13–20) se observa el intercambio de mensajes TLS, necesario para establecer una conexión segura entre el cliente y el servidor de my.usf.edu.
No hay tramas correspondientes para <www.yahoo.com> porque esa solicitud usa HTTP sin cifrado, por lo tanto, no necesita un handshake TLS.

-Look at the “Info” column on frame 6. It says: “GET / HTTP / 1.1. What is the corresponding Info
field for the my.usf.com web request (frame 21)? Why doesn’t it read the same as in frame 6?

c)En el frame 6, la columna “Info” muestra GET / HTTP/1.1, porque es una solicitud HTTP enviada en texto claro.
En el frame 21, correspondiente a my.usf.edu, la columna “Info” muestra Application Data, ya que el contenido (incluyendo el GET) está cifrado mediante TLS.
Por eso no se puede ver el mismo contenido que en el frame 6.
