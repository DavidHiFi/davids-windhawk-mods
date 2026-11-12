static void Set_OpenPopup(SetWindow& w, int k) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    const SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float boxTop = pt.box.top - w.scrollY, boxBottom = pt.box.bottom - w.scrollY;
    float h = (float)f.options.size() * kSetDropItem + 8;
    float top = boxBottom + 4;
    if (top + h > Set_ViewH(w) + 20 && boxTop - 4 - h > 0) top = boxTop - 4 - h;  // No room below: open upward.
    w.dropRect = {pt.box.left, top, pt.box.right, top + h};
    w.openSel = k;
    w.dropHover = -1;
    for (size_t i = 0; i < f.options.size(); i++)
        if (f.cur == f.options[i].first) w.dropHover = (int)i;
    Set_Invalidate(w);
}
