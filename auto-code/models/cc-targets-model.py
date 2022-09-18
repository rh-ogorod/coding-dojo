# Hey Emacs, this is -*- coding: utf-8; mode: python -*-

from subprocess import run, DEVNULL, PIPE

from pathlib import Path

workspacePath = Path(__file__).parent.resolve(True) / '..'

bazelQueryCommand = [
  'bazel',
  'query',
  '--color=no',
  '--curses=yes',
  'kind(\"(cc_binary|cc_library)\", //...)',
]

compProc = run(
  bazelQueryCommand,
  stdout=PIPE,
  stderr=DEVNULL,
  cwd=workspacePath,
)

if compProc.returncode != 0:
  raise RuntimeError(f'run() error code = {compProc.returncode}')

bazelQueryResult = compProc.stdout.decode('utf-8').split('\n')

ccTargets = [
  target for target in bazelQueryResult if target and target[:2] == '//'
]

data = {
  'ccTargets': ccTargets,
}
