int sumMatch(int * vec) {
    if (vec[0] == -1) return 0; //Caso base

    int aux = sumMatch(vec + 1);

    if (aux == 0){
        return vec[0];
    }

    return aux - vec[0];
}