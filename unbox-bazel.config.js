// Hey Emacs, this is -*- coding: utf-8 -*-

/** @type {import("./external/bazelbuild-rules-compdb").UnboxConfig} */

/** @type {UnboxConfig} */
const config = {
  ignorePaths: [
    RegExp('external/bazel_tools$'),
    RegExp('external/system$'),
    RegExp('external/cpp-utils$'),
    RegExp('bazel-out/k8-fastbuild/bin$'),
    RegExp('bazel-out/k8-fastbuild/bin/external/cpp-utils$'),
    RegExp('external/range-v3$'),
    RegExp('external/boost$'),
    RegExp('bazel-out/k8-fastbuild/bin/external/boost$'),
  ],
  pathReplacements: [
    {
      predicate: RegExp('^bazel-out/.+?/bin/external/range-v3(/?.*)'),
      replacement: 'external/range-v3$1',
    },
    {
      predicate: RegExp(
        '^bazel-out/.+?/bin/external/boost/_virtual_includes/boost-headers$',
      ),
      replacement: 'bazel-bin/external/aliens-boost/package',
    },
  ],
};

module.exports = config;
