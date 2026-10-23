// Search extracted files for a substring, print N chars of context around each match.
// Usage: node ctx.mjs <dir> <substring> [context=200] [max=10]
import fs from 'node:fs';
import path from 'node:path';

const [dir, needle, ctxArg = '250', maxArg = '8'] = process.argv.slice(2);
const ctx = Number(ctxArg), max = Number(maxArg);
let hits = 0;
function search(f) {
  if (hits >= max) return;
  const text = fs.readFileSync(f, 'utf8');
  let i = 0;
  while ((i = text.indexOf(needle, i)) !== -1 && hits < max) {
    const s = Math.max(0, i - ctx), e = Math.min(text.length, i + needle.length + ctx);
    console.log(`\n=== ${f} @${i} ===\n${text.slice(s, e)}`);
    hits++; i += needle.length;
  }
}
(function walk(d) {
  if (hits >= max) return;
  for (const ent of fs.readdirSync(d, { withFileTypes: true })) {
    const p = path.join(d, ent.name);
    if (ent.isDirectory()) walk(p);
    else if (/\.(js|mjs|cjs|html|json)$/.test(ent.name) && ent.size < 20_000_000) search(p);
  }
})(dir);
if (!hits) console.log('no matches');
