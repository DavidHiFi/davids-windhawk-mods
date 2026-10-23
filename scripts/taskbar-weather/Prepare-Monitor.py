from pathlib import Path
p=Path('C:/ProgramData/Windhawk/ModsSource/taskbar-system-info.wh.cpp')
s=p.read_text(encoding='utf-8-sig')
s=s.replace('// @id              taskbar-system-info','// @id              taskbar-system-info-weather',1)
s=s.replace('// @name            Taskbar System Info','// @name            Taskbar System Info with Weather',1)
s=s.replace('// @version         1.5.0','// @version         1.0.0',1)
marker='void ApplyWidgetGeometry(const ModSettings& settings) {'
helper='''// Local layout integration with Independent Taskbar Weather, DavidHiFi.
// The weather mod publishes its measured right edge in taskbar logical pixels.
// Fall back to the user's saved offset when that mod is absent or disabled.
double WeatherAwareLeftOffset(const ModSettings& settings) {
    HWND taskbar = g_taskbarWindow.load();
    auto edge = reinterpret_cast<INT_PTR>(
        taskbar ? GetPropW(taskbar, L"WindhawkTaskbarWeatherRightDip") : nullptr);
    return edge > 0 && edge < 2000 ? static_cast<double>(edge + 6)
                                  : static_cast<double>(settings.leftOffset);
}

'''
assert marker in s
s=s.replace(marker,helper+marker,1)
s=s.replace('Thickness{static_cast<double>(settings.leftOffset), 0, 0, 0}',
            'Thickness{WeatherAwareLeftOffset(settings), 0, 0, 0}',1)
s=s.replace('? settings.leftOffset + settings.width +','? WeatherAwareLeftOffset(settings) + settings.width +',1)
marker='''    MetricsSnapshot snapshot;
    uint64_t metricsSequence = 0;'''
assert marker in s
s=s.replace(marker,'''    if (g_widgetHost) {
        auto layoutSettings = CurrentSettings();
        double desiredLeft = WeatherAwareLeftOffset(*layoutSettings);
        auto margin = g_widgetHost.Margin();
        if (std::abs(margin.Left - desiredLeft) > 0.01) {
            margin.Left = desiredLeft;
            g_widgetHost.Margin(margin);
            ApplyReservedSpace(*layoutSettings);
        }
    }
    MetricsSnapshot snapshot;
    uint64_t metricsSequence = 0;''',1)
Path('work/taskbar-weather/taskbar-system-info.wh.cpp').write_text(s,encoding='utf-8')
print('Prepared weather-aware monitor fork; upstream credits and settings preserved.')
