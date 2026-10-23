const fs = require('node:fs');
const vm = require('node:vm');
const bundle = fs.readFileSync('C:/Program Files/Windhawk/UI/resources/app/extensions/windhawk/dist/extension.js', 'utf8');
const start = bundle.lastIndexOf('const rp=', bundle.indexOf('class lp{'));
const end = bundle.indexOf('extractInitialSettingsRaw(e){', start);
if (start < 0 || end < 0) throw new Error('Installed Windhawk parser boundaries changed');
const context = { e: fs, Q: require('node:path') };
vm.createContext(context);
vm.runInContext(bundle.slice(start, end) + '} globalThis.ModSource = lp;', context);
const parser = new context.ModSource('C:/ProgramData/Windhawk');
const path = process.argv[2] || 'C:/ProgramData/Windhawk/ModsSource/local@better-volume-mixer-plus.wh.cpp';
const source = fs.readFileSync(path, 'utf8');
try {
    const metadata = parser.extractMetadata(source, 'en');
    const readme = parser.extractReadme(source);
    if (!readme || !metadata.description || !metadata.author) throw new Error('Missing details');
    console.log(JSON.stringify({ path, metadata, readmeLength: readme.length, result: 'PASS' }, null, 2));
} catch (error) {
    console.error(JSON.stringify({ path, result: 'FAIL', error: error.message }, null, 2));
    process.exitCode = 1;
}
