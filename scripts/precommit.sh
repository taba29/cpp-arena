#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$repo_root"

echo "== clang-format =="
find src tests -name '*.cpp' -o -name '*.hpp' | xargs -I{} clang-format -i {}

echo "== build (Debug) =="
cmake --preset debug >/dev/null
cmake --build --preset debug -j

echo "== clang-tidy =="
# 簡易: 主要ターゲットに対してのみ
targets=(day1_smartptr day1_move day1_span day1_time)
for t in "${targets[@]}"; do
  clang-tidy $(jq -r '.host.toolchainFile? // empty' CMakePresets.json >/dev/null 2>&1) \
    --quiet \
    $(cmake --build build/debug --target ${t} -j --verbose 2>/dev/null | grep -Eo '(/[^ ]+\.cpp)') \
    -- -I./src || true
done

echo "== ctest =="
ctest --test-dir build/debug --output-on-failure
echo "OK"
