static float Set_ControlW(const SetField& f) {
    switch (f.kind) {
        case SetField::Check: return 40;
        case SetField::Choice: return 200;
        case SetField::Number: return f.max - f.min <= 100 ? 150 + 12 + 64 : 96;
        case SetField::Text: return 280;
        case SetField::Hotkey: return 220;
        case SetField::Color: return 362;
    }
    return 100;
}
