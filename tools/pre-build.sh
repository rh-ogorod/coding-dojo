#!/bin/bash

set -eu
set -o pipefail

SDPATH="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
if [ ! -d "${SDPATH}" ]; then SDPATH="${PWD}"; fi
readonly SDPATH="$(cd -P "${SDPATH}" && pwd)"

PRJ_ROOT_PATH="${SDPATH}/.."
readonly PRJ_ROOT_PATH="$(cd "${PRJ_ROOT_PATH}" && pwd)"

# cd "${PRJ_ROOT_PATH}/external/boost/.rh-subproject"; echo + cd "${PWD}"

# echo
# CMD=(./build.sh)
# echo + "${CMD[@]}" && "${CMD[@]}"

cd "${PRJ_ROOT_PATH}"; echo + cd "${PWD}"

echo
CMD=(bazel build "@aliens-boost//:build")
echo + "${CMD[@]}" && "${CMD[@]}"

echo
echo "unboxing ${PRJ_ROOT_PATH}/bazel-bin/external/aliens-boost/package..."

cd "${PRJ_ROOT_PATH}/bazel-bin/external/aliens-boost"

find package -type d -exec chmod u+w '{}' \;

while read -r link; do
  ln -fs "$(readlink -f "${link}")" "${link}"
  # CMD=(ln -fs "$(readlink -f "${link}")" "${link}")
  # echo + "${CMD[@]}" && "${CMD[@]}"
done <<< "$(find "package" -type l)"

echo "unboxing done"
