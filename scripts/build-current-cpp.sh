#!/usr/bin/env bash

set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <cpp-file>" >&2
  exit 1
fi

workspace_root="$(cd "$(dirname "$0")/.." && pwd)"
source_file="$1"
compiler="/usr/bin/clang++"
compat_dir="${workspace_root}/.competition-compat"

if [[ ! -f "${source_file}" ]]; then
  echo "Source file not found: ${source_file}" >&2
  exit 1
fi

source_dir="$(cd "$(dirname "${source_file}")" && pwd)"
source_name="$(basename "${source_file}")"
source_abs="${source_dir}/${source_name}"

case "${source_abs}" in
  "${workspace_root}"/*) ;;
  *)
    echo "Source file must be inside the workspace: ${source_abs}" >&2
    exit 1
    ;;
esac

relative_path="${source_abs#${workspace_root}/}"
relative_dir="$(dirname "${relative_path}")"
basename_no_ext="${source_name%.cpp}"
output_dir="${workspace_root}/build/bin-single/${relative_dir}"
output_path="${output_dir}/${basename_no_ext}"
current_debug_link="${workspace_root}/build/bin-single/current-debug-target"

mkdir -p "${output_dir}"

 "${compiler}" \
  -std=gnu++17 \
  -Wall \
  -Wextra \
  -g \
  -finput-charset=UTF-8 \
  -fexec-charset=UTF-8 \
  -I"${compat_dir}" \
  "${source_abs}" \
  -o "${output_path}"

# CodeLLDB on macOS can be flaky with non-ASCII executable paths.
# Keep a stable ASCII symlink for launching the most recently built file.
ln -sfn "${output_path}" "${current_debug_link}"
