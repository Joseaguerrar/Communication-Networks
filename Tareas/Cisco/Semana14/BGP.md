# Packet Tracer - Configurar y Verificar eBGP

## Objetivos

- Configurar y verificar eBGP entre dos sistemas autónomos (AS 65001 y AS 65002).
- Comprobar la conectividad entre las redes de ACME Inc. y Other Company a través del ISP (AS 65003).

---

## Escenario

ACME Inc. se ha asociado con Other Company y necesita intercambiar rutas. Ambas empresas tienen su propio sistema autónomo y utilizan un ISP como tránsito para comunicarse entre sí. Esta actividad implica configurar eBGP entre los routers fronterizos de cada compañía y el ISP para permitir el intercambio de rutas.

> Nota: Solo compañías con redes muy grandes pueden permitirse su propio sistema autónomo.

---

## Tabla de Direcciones

| Dispositivo | Interfaz  | Dirección IPv4 | Máscara de Subred | Gateway por Defecto |
|-------------|-----------|----------------|--------------------|----------------------|
| ACME1       | G0/0      | 192.168.0.1    | 255.255.255.0      | N/A                  |
| ACME1       | S0/0/0    | 1.1.1.2        | 255.255.255.252    | N/A                  |
| OtherCo1    | G0/0      | 172.16.10.1    | 255.255.255.0      | N/A                  |
| OtherCo1    | S0/0/0    | 1.1.1.10       | 255.255.255.252    | N/A                  |
| ISP1        | S0/0/0    | 1.1.1.1        | 255.255.255.252    |                      |
| ISP1        | S0/0/1    | 1.1.1.5        | 255.255.255.252    |                      |
| ISP2        | S0/0/0    | 1.1.1.9        | 255.255.255.252    |                      |
| ISP2        | S0/0/1    | 1.1.1.6        | 255.255.255.252    |                      |
| PC0         | NIC       | DHCP           |                    | 192.168.0.1          |
| Laptop0     | NIC       | DHCP           |                    | 192.168.0.1          |
| Laptop1     | NIC       | DHCP           |                    | 192.168.0.1          |
| Server      | NIC       | 172.16.10.2    | 255.255.255.0      | 172.16.10.1          |

---

## Paso 1: Configurar eBGP en ACME Inc

### a. Verificar conectividad con ISP

1. En el router **ACME1**, acceda al modo EXEC privilegiado:

```bash
enable
```

Verifique la conectividad hacia el ISP (ISP2) haciendo ping a la IP 1.1.1.9:

```bash
ping 1.1.1.9
```

Si el ping falla, asegúrese de que las interfaces seriales estén activadas (no shutdown) y correctamente configuradas.

b. Verificar que no hay conectividad con la red de Other Company
Desde un dispositivo dentro de la red de ACME (por ejemplo, PC0, Laptop0, o Laptop1):

Abra la terminal.

Realice un ping al servidor de Other Company:

```bash
ping 172.16.10.2
```

El ping debe fallar en este punto, ya que no hay rutas BGP configuradas.

c. Configurar eBGP en ACME1
En el router ACME1, entre al modo de configuración global:

```bash
configure terminal
```

Inicie el proceso de BGP utilizando el número de AS de ACME (65001):

```bash
router bgp 65001
```

Establezca una vecindad BGP con el ISP (AS 65003), usando la IP del vecino:

```bash
neighbor 1.1.1.1 remote-as 65003
```

Anuncie la red interna de ACME a través de BGP:

```bash
network 192.168.0.0 mask 255.255.255.0
```

Salga del modo de configuración y guarde los cambios:

```bash
end
write memory
```

d. Verificar conectividad nuevamente
Desde cualquier dispositivo dentro de ACME (PC0, Laptop0, Laptop1), intente hacer ping al servidor de Other Company:

```bash
ping 172.16.10.2
```

Aún fallará, ya que falta configurar eBGP en Other Company.

## Paso 2: Configurar eBGP en Other Company Inc

### a. Configurar eBGP en OtherCo1

1. Acceda a la consola del router **OtherCo1**.
2. Entre al modo de configuración global:

```bash
enable
configure terminal
```

3.Inicie el proceso BGP para el AS de Other Company (65002):

```bash
router bgp 65002
```

4.Configure como vecino BGP a ISP2, que está en el AS 65003, con IP 1.1.1.9:

```bash
neighbor 1.1.1.9 remote-as 65003
```

5.Anuncie la red interna de Other Company (172.16.10.0/24):

```bash
network 172.16.10.0 mask 255.255.255.0
```

6.Finalice y guarde los cambios:

```bash
end
write memory
```

### b. Verificar la vecindad eBGP en OtherCo1

1.Ejecute el siguiente comando:

```bash
show ip bgp summary
```

Verifique que:

**El vecino 1.1.1.9 esté en estado Established.**

**Se estén recibiendo rutas BGP (State/PfxRcd debe ser > 0).**

### c. Verificar las rutas aprendidas

1.En OtherCo1, verifique que la red de ACME esté siendo aprendida:

```bash
show ip bgp
```

Debería ver una entrada similar a:

```bash
*> 192.168.0.0/24    1.1.1.9     0     0     0 65003 ?
```

2.También puede revisar la tabla de enrutamiento:

```bash
show ip route
```

Allí debería ver la red 192.168.0.0/24 aprendida vía BGP (B).

### d. Probar conectividad desde ACME hacia Other Company

1.Desde cualquier dispositivo de ACME (PC0, Laptop0, Laptop1):

Abra la terminal y ejecute:

```bash
ping 172.16.10.2
```

2.El ping debe tener éxito. Si es así, la comunicación entre ambas empresas está funcionando correctamente.

e. (Opcional) Acceder al servidor web
Desde cualquier dispositivo en ACME, abra el navegador.

Escriba en la barra de direcciones:

```bash
<http://172.16.10.2>
```

3.Debería ver la página del servidor de Other Company, confirmando conectividad de capa 7.
