from pathlib import Path
import subprocess
import os
import argparse

parser = argparse.ArgumentParser(description='Test the mod network collector with controlled Windows interface counters.')
parser.add_argument('--source', type=Path)
parser.add_argument('--output-dir', type=Path)
args = parser.parse_args()
script = Path(__file__).resolve().parent
default_source = script / 'repo/mods/local/taskbar-system-info-weather/taskbar-system-info-weather.wh.cpp'
if not default_source.exists():
    default_source = script.parent / 'taskbar-system-info-weather.wh.cpp'
root = args.output_dir or script / 'output'
root.mkdir(parents=True, exist_ok=True)
source = (args.source or default_source).read_text(encoding='utf-8')
network = source[source.index('struct NetworkCounters'):source.index('MetricsSnapshot CollectMetrics')]
fixed = source[source.index('std::wstring FormatFixed'):source.index('std::wstring FormatPercent')]
test = r'''
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <netioapi.h>
#include <chrono>
#include <unordered_map>
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
using SampleTime = std::chrono::steady_clock::time_point;
struct MetricsSnapshot {double uploadBps=0,downloadBps=0;bool networkAvailable=false;};
MIB_IF_TABLE2 mock{};
bool fail=false;
DWORD TestGetIfTable2(MIB_IF_TABLE2** table) {*table=&mock;return fail ? ERROR_NOT_FOUND : NO_ERROR;}
void TestFreeMibTable(void*) {}
#define GetIfTable2 TestGetIfTable2
#define FreeMibTable TestFreeMibTable
'''
test += network + fixed + r'''
int main() {
 auto& row=mock.Table[0]; mock.NumEntries=1;
 row.OperStatus=IfOperStatusUp;row.InterfaceAndOperStatusFlags.HardwareInterface=1;
 row.Type=IF_TYPE_ETHERNET_CSMACD;row.InterfaceLuid.Value=42;
 row.InOctets=1000;row.OutOctets=2000;
 MetricsSnapshot a;ReadNetwork(a,true);assert(!a.networkAvailable);
 row.InOctets+=10000;row.OutOctets+=5000;
 g_networkSampleTime=std::chrono::steady_clock::now()-std::chrono::seconds(2);
 MetricsSnapshot b;ReadNetwork(b,true);assert(b.networkAvailable);
 assert(std::abs(b.downloadBps-5000)<1 && std::abs(b.uploadBps-2500)<1);
 g_networkSampleTime=std::chrono::steady_clock::now()-std::chrono::seconds(1);
 MetricsSnapshot idle;ReadNetwork(idle,true);assert(idle.networkAvailable && idle.uploadBps==0);
 row.InOctets=1;row.OutOctets=1;
 MetricsSnapshot reset;ReadNetwork(reset,true);assert(!reset.networkAvailable);
 row.InterfaceLuid.Value=43;
 MetricsSnapshot changed;ReadNetwork(changed,true);assert(!changed.networkAvailable);
 row.InterfaceAndOperStatusFlags.HardwareInterface=0;
 MetricsSnapshot virtualRow;ReadNetwork(virtualRow,true);assert(!virtualRow.networkAvailable && g_networkPrevious.empty());
 row.InterfaceAndOperStatusFlags.HardwareInterface=1;row.Type=IF_TYPE_SOFTWARE_LOOPBACK;
 MetricsSnapshot loopback;ReadNetwork(loopback,true);assert(!loopback.networkAvailable);
 row.Type=IF_TYPE_ETHERNET_CSMACD;row.OperStatus=IfOperStatusDown;
 MetricsSnapshot down;ReadNetwork(down,true);assert(!down.networkAvailable);
 row.OperStatus=IfOperStatusUp;
 MetricsSnapshot baseline;ReadNetwork(baseline,true);
 fail=true;MetricsSnapshot failure;ReadNetwork(failure,true);assert(!failure.networkAvailable && g_networkPrevious.empty());
 fail=false;MetricsSnapshot retry;ReadNetwork(retry,true);assert(!retry.networkAvailable);
 MetricsSnapshot disabled;ReadNetwork(disabled,false);assert(g_networkPrevious.empty());
 assert(FormatNetworkSpeed(0,true,true)==L"↑ 0 B/s");
 assert(FormatNetworkSpeed(1234,true,false)==L"↓ 1.2 KB/s");
 assert(FormatNetworkSpeed(1234567,true,true)==L"↑ 1.2 MB/s");
 assert(FormatNetworkSpeed(1e9,true,false)==L"↓ 1.0 GB/s");
 assert(FormatNetworkSpeed(1e12,true,false)==L"↓ 1.0 TB/s");
 assert(FormatNetworkSpeed(0,false,true)==L"↑ -- B/s");
 assert(FormatNetworkSpeed(NAN,true,false)==L"↓ -- B/s");
 std::cout<<"PASS: baseline, elapsed-time rates, idle, reset, adapter switch, virtual/loopback/down filters, failure recovery, disable, units and missing values\n";
}
'''
(root / 'test_network.cpp').write_text(test,encoding='utf-8')
compiler = r'C:\Program Files\Windhawk\Compiler\bin\clang++.exe'
subprocess.run([compiler,'-std=c++23','-O2','-static','-target','x86_64-w64-mingw32',str(root/'test_network.cpp'),'-o',str(root/'test_network.exe')],check=True)
env = dict(os.environ)
env['PATH'] = str(Path(compiler).parent.parent / 'x86_64-w64-mingw32/bin') + os.pathsep + env['PATH']
subprocess.run([str(root/'test_network.exe')],check=True,env=env)
