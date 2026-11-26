//! Hidden child processes. Nothing the engine starts ever shows a window.

use anyhow::{Context, Result};
use std::io::{BufReader, Read};
use std::os::windows::process::CommandExt;
use std::process::{Command, Stdio};

pub const CREATE_NO_WINDOW: u32 = 0x0800_0000;

pub struct Out {
    pub code: i32,
    pub stdout: Vec<u8>,
    pub stderr: Vec<u8>,
}

impl Out {
    /// stdout + stderr as text. Handles the UTF-16 that sfc and some tools write to pipes.
    pub fn text(&self) -> String {
        let mut s = decode(&self.stdout);
        let e = decode(&self.stderr);
        if !e.trim().is_empty() {
            s.push('\n');
            s.push_str(&e);
        }
        s
    }
}

/// UTF-16LE when every other byte is mostly zero, else UTF-8 (lossy).
pub fn decode(b: &[u8]) -> String {
    if b.len() >= 4 {
        let odd_zero = b.iter().skip(1).step_by(2).filter(|&&c| c == 0).count();
        if odd_zero * 3 > b.len() / 2 * 2 {
            let w: Vec<u16> = b.chunks_exact(2).map(|c| u16::from_le_bytes([c[0], c[1]])).collect();
            return String::from_utf16_lossy(&w).replace('\u{feff}', "");
        }
    }
    String::from_utf8_lossy(b).into_owned()
}

fn cmd(exe: &str, args: &[&str]) -> Command {
    let mut c = Command::new(exe);
    c.args(args).creation_flags(CREATE_NO_WINDOW).stdin(Stdio::null());
    c
}

/// Run and wait. Never shows a window.
pub fn run(exe: &str, args: &[&str]) -> Result<Out> {
    let o = cmd(exe, args).output().with_context(|| format!("start {exe}"))?;
    Ok(Out { code: o.status.code().unwrap_or(-1), stdout: o.stdout, stderr: o.stderr })
}

/// Run and call `line` for each output line as it arrives (DISM and sfc progress).
/// Lines split on \r and \n, so progress bars that redraw with \r come through.
pub fn run_lines(exe: &str, args: &[&str], mut line: impl FnMut(&str)) -> Result<i32> {
    let mut child = cmd(exe, args).stdout(Stdio::piped()).stderr(Stdio::null()).spawn().with_context(|| format!("start {exe}"))?;
    let mut out = BufReader::new(child.stdout.take().unwrap());
    let mut buf = Vec::new();
    let mut chunk = [0u8; 4096];
    let mut utf16: Option<bool> = None;
    loop {
        let n = out.read(&mut chunk)?;
        if n == 0 {
            break;
        }
        buf.extend_from_slice(&chunk[..n]);
        if utf16.is_none() && buf.len() >= 8 {
            utf16 = Some(buf.iter().skip(1).step_by(2).take(16).filter(|&&c| c == 0).count() >= 3);
        }
        let wide = utf16.unwrap_or(false);
        // Cut complete lines off the front of buf.
        loop {
            let pos = if wide {
                buf.chunks_exact(2).position(|c| (c[0] == b'\n' || c[0] == b'\r') && c[1] == 0).map(|i| i * 2)
            } else {
                buf.iter().position(|&c| c == b'\n' || c == b'\r')
            };
            let Some(p) = pos else { break };
            let piece: Vec<u8> = buf.drain(..p).collect();
            buf.drain(..if wide { 2 } else { 1 });
            let s = if wide { decode(&piece) } else { String::from_utf8_lossy(&piece).into_owned() };
            let t = s.trim();
            if !t.is_empty() {
                line(t);
            }
        }
    }
    if !buf.is_empty() {
        let s = decode(&buf);
        if !s.trim().is_empty() {
            line(s.trim());
        }
    }
    Ok(child.wait()?.code().unwrap_or(-1))
}

/// Run PowerShell hidden with a script, no profile. Use only when there is no API.
pub fn powershell(script: &str) -> Result<Out> {
    run("powershell.exe", &["-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-Command", script])
}
