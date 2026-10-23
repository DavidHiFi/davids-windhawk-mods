// Probe the grok CLI's ACP stdio: initialize + session/new, dump everything it sends.
import { spawn } from 'node:child_process';

const bin = String.raw`C:\Users\localuser\AppData\Roaming\npm\node_modules\@xai-official\grok\bin\grok`;
const node = String.raw`C:\Program Files\nodejs\node.exe`;
const child = spawn(node, [bin, 'agent', 'stdio'], { stdio: ['pipe', 'pipe', 'pipe'] });

let buf = '';
child.stdout.on('data', d => {
  buf += d.toString();
  let idx;
  while ((idx = buf.indexOf('\n')) !== -1) {
    const line = buf.slice(0, idx).trim();
    buf = buf.slice(idx + 1);
    if (!line) continue;
    try {
      const msg = JSON.parse(line);
      console.log('<<', JSON.stringify(msg).slice(0, 3000));
    } catch { console.log('<< (non-json)', line.slice(0, 300)); }
  }
});
child.stderr.on('data', d => console.error('ERR>', d.toString().slice(0, 500)));
child.on('exit', c => { console.log('exit', c); process.exit(0); });

const send = o => { console.log('>>', JSON.stringify(o).slice(0, 300)); child.stdin.write(JSON.stringify(o) + '\n'); };

send({ jsonrpc: '2.0', id: 1, method: 'initialize', params: { protocolVersion: 1, clientCapabilities: {} } });

setTimeout(() => {
  send({ jsonrpc: '2.0', id: 2, method: 'session/new', params: { cwd: 'H:\\Windhawk Configuration', mcpServers: [] } });
}, 2500);

setTimeout(() => { console.log('-- done --'); child.kill(); process.exit(0); }, 20000);
