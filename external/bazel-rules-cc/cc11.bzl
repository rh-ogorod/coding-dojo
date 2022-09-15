# Hey Emacs, this is -*- coding: utf-8; mode: bazel -*-

load(
  "@rules_cc//cc:defs.bzl",
  cc_binary_orig = "cc_binary",
  cc_library_orig = "cc_library",
  cc_test_orig = "cc_test",
)

load(":cc_common.bzl", "append_to_copts")

STD="-std=c++11"

def cc_library(**kwargs):
  append_to_copts(kwargs, STD)
  cc_library_orig(**kwargs)

def cc_binary(**kwargs):
  append_to_copts(kwargs, STD)
  cc_binary_orig(**kwargs)

def cc_test(**kwargs):
  append_to_copts(kwargs, STD)
  cc_test_orig(**kwargs)
