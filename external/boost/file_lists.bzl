# Hey Emacs, this is -*- coding: utf-8; mode: bazel -*-

staticLibsTest = (
  "libboost_prg_exec_monitor-gcc11-mt-x64-1_80.a",
  "libboost_test_exec_monitor-gcc11-mt-x64-1_80.a",
  "libboost_unit_test_framework-gcc11-mt-x64-1_80.a",
)

sharedLibsTest = (
  "libboost_prg_exec_monitor-gcc11-mt-x64-1_80.so",
  "libboost_prg_exec_monitor-gcc11-mt-x64-1_80.so.1.80.0",
  "libboost_unit_test_framework-gcc11-mt-x64-1_80.so",
  "libboost_unit_test_framework-gcc11-mt-x64-1_80.so.1.80.0",
)

staticLibs = (
  "libboost_system-gcc11-mt-x64-1_80.a",
)

sharedLibs = (
  # "libboost_system-gcc11-mt-x64-1_80.so",
  "libboost_system-gcc11-mt-x64-1_80.so.1.80.0",
)
