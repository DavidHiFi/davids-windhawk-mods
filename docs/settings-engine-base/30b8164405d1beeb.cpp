static int Set_CapButtonAt(const SetWindow& w, float x, float y) {
    if (w.nativeTitle || w.nativeButtons) return -1;
    for (int i = 0; i < 3; i++)
        if (Set_In(Set_CapButton(w, i), x, y + kSetCapH)) return i;
    return -1;
}
