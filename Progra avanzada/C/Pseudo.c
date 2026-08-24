void coloring(Grafo){

    for nodo in grafo{
        if delta(nodo) != 3{
            nodo_central = g
            Secolor(nodo) = 3
            set.visited(nodo)
        }
        if delta(nodo) == 3{
            inicial = nodo
        }
    }
    color_actual = 1
    set.color(inicial) = color_actual
    set.visited(inicial)
    if delta(g) % 2 == 0 {
        for p adyacente inicial in grafo: {
            if not get(visited(p)){
                set.color(p) = color_actual % 2 + 1
                color_actual++
                inicial = p
                ser.visited(p)
            }
        if len(visitados) != delta(nodo_cental) + 1 : break
        }
    }
    else {
        for p adyacente inicial in grafo: {
            if not get(visited(p) && color_actual % 2 + 1 != get.color(inicial)){
                set.color(p) = color_actual % 2 + 1
                set.visited(p)
                color_actual++
                inicial = p
            }
            else if not get.visited(p){
                set.color(p) = 4
                set.visited(p)
                color_actual++
                inicial = p
            }
        }
        if len(visitados) != delta(nodo_cental) + 1 : break
    }
}

//lo que hacemos es encontrar el vertice central y colorearlo, luego, definimos un vertice inicial,
// lo coloreamos y recorremos los vertices adyacentes a el y coloreamos alternadamente, 
//exepto si el ciclo es impar, en ese caso coloreamos el ultimo nodo con otro color, el 4