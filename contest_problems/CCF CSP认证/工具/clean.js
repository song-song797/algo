const fs = require('fs');
const path = require('path');

const cspDir = path.resolve(__dirname, '..');
const d = path.join(cspDir, 'round01');
let count = 0;

fs.readdirSync(d).filter(x => x.includes('_第')).forEach(dir => {
  const p = path.join(d, dir);
  if (!fs.statSync(p).isDirectory()) return;

  fs.readdirSync(p).filter(f => f.endsWith('.cpp')).forEach(f => {
    const fp = path.join(p, f);
    let c = fs.readFileSync(fp, 'utf8');
    const m = c.match(/\/\*[\s\S]*?\*\//);
    if (!m) return;

    let cm = m[0];
    if (cm.includes('题目描述：')) {
      cm = cm.split('题目描述：')[0].trim();
      if (!cm.endsWith('*/')) cm += '\n */';
    }

    const codeStart = c.indexOf(m[0]) + m[0].length;
    let code = c.substring(codeStart).trim();
    const codeNoSpace = code.replace(/\s+/g, '');

    if (codeNoSpace === '#include<iostream>usingnamespacestd;intmain(){return0;}' || codeNoSpace === 'usingnamespacestd;intmain(){return0;}') {
      code = '';
    }

    const nc = cm + (code ? '\n\n' + code : '');
    if (c.trim() !== nc.trim()) {
      fs.writeFileSync(fp, nc.trim() + '\n\n');
      console.log('Updated: ' + f);
      count++;
    }
  });
});

console.log(`Finished processing. Updated ${count} files.`);
fs.writeFileSync(path.join(cspDir, 'js_done.txt'), 'done ' + count);
