# Hey Emacs, this is -*- coding: utf-8; mode: bazel -*-

load("@rules_cc//cc:action_names.bzl", "ACTION_NAMES")

load(
  "@rules_cc//cc:cc_toolchain_config_lib.bzl",
  "feature",
  "flag_group",
  "flag_set",
  "tool_path",
)

all_link_actions = [
  ACTION_NAMES.cpp_link_executable,
  ACTION_NAMES.cpp_link_dynamic_library,
  ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

all_compile_actions = [
  ACTION_NAMES.assemble,
  ACTION_NAMES.c_compile,
  ACTION_NAMES.clif_match,
  ACTION_NAMES.cpp_compile,
  ACTION_NAMES.cpp_header_parsing,
  ACTION_NAMES.cpp_module_codegen,
  ACTION_NAMES.cpp_module_compile,
  ACTION_NAMES.linkstamp_compile,
  ACTION_NAMES.lto_backend,
  ACTION_NAMES.preprocess_assemble,
]

def _impl(ctx):
  [major, minor, patch] = ctx.attr.clang_version
  version = "{}.{}.{}".format(major, minor, patch)

  tool_paths = [
    tool_path(
      name = "gcc",
      path = "/usr/bin/clang-{}".format(major),
    ),
    tool_path(
      name = "ld",
      path = "/usr/bin/ld.gold",
    ),
    tool_path(
      name = "ar",
      path = "/usr/bin/ar",
    ),
    tool_path(
      name = "cpp",
      path = "/bin/false",
    ),
    tool_path(
      name = "gcov",
      path = "/bin/false",
    ),
    tool_path(
      name = "nm",
      path = "/bin/false",
    ),
    tool_path(
      name = "objdump",
      path = "/bin/false",
    ),
    tool_path(
      name = "strip",
      path = "/bin/false",
    ),
  ]


  default_compiler_flags = feature(
    name = "default_compiler_flags",
    enabled = True,
    flag_sets = [
      flag_set(
        actions = all_compile_actions,
        flag_groups = [
          flag_group(
            flags = [
              "-std=c++20",
              # "--sysroot=external/aarch64-rpi3-linux-gnu-sysroot",
              # "-no-canonical-prefixes",
              # "-fno-canonical-system-headers",
              # "-Wno-builtin-macro-redefined",
              # "-D__DATE__=\"redacted\"",
              # "-D__TIMESTAMP__=\"redacted\"",
              # "-D__TIME__=\"redacted\"",
            ],
          ),
        ],
      ),
    ],
  )

  default_linker_flags = feature(
    name = "default_linker_flags",
    enabled = True,
    flag_sets = [
      flag_set(
        actions = all_link_actions,
        flag_groups = ([
          flag_group(
            flags = [
              # "--sysroot=external/aarch64-rpi3-linux-gnu-sysroot",
              "-lstdc++",
            ],
          ),
        ]),
      ),
    ],
  )

  features = [
    default_compiler_flags,
    default_linker_flags,
  ]

  return cc_common.create_cc_toolchain_config_info(
    ctx = ctx,
    features = features,
    cxx_builtin_include_directories = [
      "/usr/lib/llvm-14/lib/clang/{}/include".format(version),
      "/usr/include",
    ],
    toolchain_identifier = \
      "x86_64-clang-{}-toolchain".format(version),
    host_system_name = "local",
    target_system_name = "local",
    target_cpu = "x86_64",
    target_libc = "unknown",
    compiler = "clang-{}".format(version),
    abi_version = "unknown",
    abi_libc_version = "unknown",
    tool_paths = tool_paths,
  )

x86_64_linux_clang_cc_toolchain_config = rule(
  implementation = _impl,
  attrs = {
    "clang_version": attr.int_list(
      mandatory = True,
      doc = "clang version: [major, minor, patch]",
    ),
  },
  provides = [CcToolchainConfigInfo],
)
