# Tarea 1.1
![Tarea1.1](../Images/tarea1.1.png)




## 2. Diámetro de la Red

El diámetro de una red es la ruta más corta más larga entre cualquier par de nodos.

Para determinarlo, se calcula el camino más corto entre todos los pares posibles de nodos y se identifica cuál de ellos tiene la mayor cantidad de saltos.

Después de analizar el grafo, uno de los caminos más largos entre los caminos más cortos es: H → A → C → J → F (Hay otros con esta cantidad).


Este camino tiene **4 saltos**.

Por lo tanto, el **diámetro de la red es 4**.

## 3. Ancho de Banda de Bisección (Bisection Bandwidth)

El ancho de banda de bisección se determina dividiendo el conjunto de nodos en dos subconjuntos de tamaño igual o casi igual, y contando cuántos enlaces deben ser cortados para separar completamente ambos grupos.

En este caso, se propone la siguiente partición:

- **Grupo 1**: A, H, D, E  
- **Grupo 2**: B, C, G, F, J

Al analizar las conexiones entre estos dos grupos, se identifican los siguientes enlaces que cruzan la partición:

- A — B  
- A — C  
- E — C

**Total de enlaces que cruzan:** 3

Por lo tanto, el **ancho de banda de bisección (bisection bandwidth)** de esta red es:

**Bisection Bandwidth = 3**


