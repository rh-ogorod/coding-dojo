#!/bin/bash

set -eu
set -o pipefail

SDPATH="$(dirname $(realpath "${BASH_SOURCE[0]}"))"
if [[ ! -d "${SDPATH}" ]]; then SDPATH="${PWD}"; fi
readonly SDPATH="$(cd -P "${SDPATH}" && pwd)"

PRJ_ROOT_PATH="${SDPATH}/.."
readonly PRJ_ROOT_PATH="$(cd "${PRJ_ROOT_PATH}" && pwd)"

cd "${PRJ_ROOT_PATH}/auto-code/main" && echo cd "${PWD}"

CMD=(./auto-code-groups)
echo + "${CMD[@]}" && "${CMD[@]}"
