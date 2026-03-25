#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH="${ROOT}/uhd-local/bin:${PATH}"
export LD_LIBRARY_PATH="${ROOT}/srsue_build/lib/src/phy/rf:${ROOT}/uhd-local/lib:${LD_LIBRARY_PATH:-}"
export UHD_IMAGES_DIR="${ROOT}/uhd_images"

exec "${ROOT}/srsue_build/srsue/src/srsue" "${ROOT}/configs/ue_5gsa_srsproject_b200_20mhz.conf" "$@"
