#!/bin/bash

set -eu
set -o pipefail

SDPATH="$(dirname "${BASH_SOURCE[0]}")"
if [[ ! -d "${SDPATH}" ]]; then SDPATH="${PWD}"; fi
readonly SDPATH="$(cd -P "${SDPATH}" && pwd)"

PRJ_ROOT_PATH="${SDPATH}/.."
readonly PRJ_ROOT_PATH="$(cd "${PRJ_ROOT_PATH}" && pwd)"

cd "${SDPATH}"; echo cd "${PWD}"

CMD=(./git-populate-submodules.sh)
echo + "${CMD[@]}" && "${CMD[@]}"

echo
cd "${PRJ_ROOT_PATH}/external/boost/.rh-subproject"; echo cd "${PWD}"

echo
CMD=(./bootstrap.sh)
echo + "${CMD[@]}" && "${CMD[@]}"

echo
CMD=(yarn)
echo + "${CMD[@]}" && "${CMD[@]}"
