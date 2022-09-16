# Hey Emacs, this is -*- coding: utf-8; mode: python -*-

from pathlib import Path

generatorsPath = Path(__file__).parent.resolve(True) / 'main'

projectRootPath = (generatorsPath / '..' / '..').resolve(True)

autoCodeDirectories = [
  str(projectRootPath / 'packages'),
]

autoCodeFiles = r'\.xxx$'
