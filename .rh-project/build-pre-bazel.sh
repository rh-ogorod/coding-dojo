#!/bin/bash

set -eu
set -o pipefail

SDPATH="$(dirname "${BASH_SOURCE[0]}")"
if [ ! -d "${SDPATH}" ]; then SDPATH="${PWD}"; fi
readonly SDPATH="$(cd -P "${SDPATH}" && pwd)"

# shellcheck source=./conf.sh
source "${SDPATH}/conf.sh"

cd "${PRJ_ROOT_PATH}/external/boost/.rh-subproject"; echo + cd "${PWD}"

echo
CMD=(./build.sh)
echo + "${CMD[@]}" && "${CMD[@]}"
