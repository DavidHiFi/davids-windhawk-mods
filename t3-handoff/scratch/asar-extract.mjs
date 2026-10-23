// Minimal asar reader: list files or extract matching files.
// Usage: node asar-extract.mjs <archive> <list|extract> <substrFilter> [outDir]
import fs from 'node:fs';
import path from 'node:path';

const [archive, mode, filter = '', outDir = ''] = process.argv.slice(2);
const fd = fs.openSync(archive, 'r');
const sizeBuf = Buffer.alloc(8);
fs.readSync(fd, sizeBuf, 0, 8, 0);
const headerSize = sizeBuf.readUInt32LE(4);
const headerBuf = Buffer.alloc(headerSize);
fs.readSync(fd, headerBuf, 0, headerSize, 8);
const jsonLen = headerBuf.readUInt32LE(4);
const json = JSON.parse(headerBuf.slice(8, 8 + jsonLen).toString('utf8'));
const baseOffset = 8 + headerSize;

function walk(node, prefix) {
  if (node.files) {
    for (const [name, child] of Object.entries(node.files)) walk(child, path.join(prefix, name));
  } else if (node.offset !== undefined) {
    files.push({ file: prefix, offset: Number(node.offset), size: node.size, unpacked: !!node.unpacked });
  }
}
const files = [];
walk(json, '');

const matches = files.filter(f => f.file.toLowerCase().includes(filter.toLowerCase()));
if (mode === 'list') {
  for (const m of matches) console.log(`${m.file}  ${m.size}`);
} else {
  for (const m of matches) {
    const dest = path.join(outDir, ...m.file.split(path.sep));
    fs.mkdirSync(path.dirname(dest), { recursive: true });
    const buf = Buffer.alloc(m.size);
    fs.readSync(fd, buf, 0, m.size, baseOffset + m.offset);
    fs.writeFileSync(dest, buf);
    console.log(`extracted ${m.file} (${m.size})`);
  }
}
console.error(`total files: ${files.length}, matched: ${matches.length}`);
