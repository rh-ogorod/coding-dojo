#!/bin/bash

set -eu
set -o pipefail

SDPATH="$(dirname "${BASH_SOURCE[0]}")"
if [ ! -d "${SDPATH}" ]; then SDPATH="${PWD}"; fi
readonly SDPATH="$(cd -P "${SDPATH}" && pwd)"

bazel query --color=no --curses=yes 'kind("(cc_binary|cc_library)", //...)' 2>/dev/null | grep '//packages'
