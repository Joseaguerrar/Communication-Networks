# Quiz #2

---

## 1. ¿El esquema de comunicación Bluetooth pertenece a la familia de protocolos ?

**Respuesta:**  
IEEE **802.15**  

---

## 2. Escriba una ventaja de un protocolo de paso de token: 

**Respuesta:**  
**Evita colisiones al controlar el acceso al medio compartido.**  

---

## 3. Con mi carnet C33510 tenemos la siguiente dirección IPv4  

**35.122.127.0/17**  
(donde `c1c2c3c4c5c6` representa el número de carné `C33510`, lo que da como número representativo `35`), indique lo siguiente:

### Respuestas

- **Dirección IP de la red:** `35.122.0.0`  
- **Dirección IP para el primer host:** `35.122.0.1`  
- **Dirección IP para el último host:** `35.122.127.254`  
- **Dirección IP para broadcast:** `35.122.127.255`

### Explicación

- Una máscara `/17` equivale a `255.255.128.0`, lo que cubre desde `35.122.0.0` hasta `35.122.127.255`.
- El tercer octeto forma parte parcialmente de la red, ya que solo su primer bit se considera en la parte de red.
- 2¹⁵ = 32,768 direcciones totales.

---

## 4. Asignación de subredes con la base `192.168.80.0`  

Se solicitan:

- **Rango A**: 64 direcciones utilizables  
- **Rango B**: 127 direcciones utilizables (más grande → se acomoda primero)  
- **Rango C**: 63 direcciones utilizables  

### Asignaciones finales

| Rango | Dirección de red     | Máscara              | Rango de Hosts                   | Broadcast            |
|-------|----------------------|----------------------|----------------------------------|----------------------|
| B     | 192.168.80.0         | /24 (255.255.255.0)  | 192.168.80.1 – 192.168.80.254    | 192.168.80.255       |
| A     | 192.168.81.0         | /26 (255.255.255.192)| 192.168.81.1 – 192.168.81.62     | 192.168.81.63        |
| C     | 192.168.81.64        | /26 (255.255.255.192)| 192.168.81.65 – 192.168.81.126   | 192.168.81.127       |

### Notas

- Rango B necesita más de 126 direcciones utilizables, así que se le asigna un bloque **/24**.
- Rangos A y C se ajustan con **/26**.
