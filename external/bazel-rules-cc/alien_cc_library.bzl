# Hey Emacs, this is -*- coding: utf-8; mode: bazel -*-

load(
  "@bazel_tools//tools/cpp:toolchain_utils.bzl",
  # "find_cpp_toolchain",
  "use_cpp_toolchain",
)

# load(
#   "@rules_cc//cc:action_names.bzl",
#   "CPP_LINK_STATIC_LIBRARY_ACTION_NAME"
# )

def _alien_cc_library_impl(ctx):
  path = ctx.attr.dep_gen[DefaultInfo].files.to_list()[0].path
  print('xxx', ctx.attr.dep_gen[DefaultInfo].files.to_list()[1])
  args = ctx.actions.args()
  args.add_all([ctx.attr.dep_gen[DefaultInfo].files.to_list()[1]])

  out = ctx.actions.declare_file(ctx.label.name)

  ctx.actions.run_shell(
    command="echo $@ > " + out.path,
    arguments=[args],
    outputs=[out],
    inputs=[ctx.attr.dep_gen[DefaultInfo].files.to_list()[1]]
  )

  print('args', args)

  # cc_toolchain = find_cpp_toolchain(ctx)
  # object_file = ctx.attr.object[MyCCompileInfo].object
  # output_file = ctx.actions.declare_file(ctx.label.name + ".a")

  # feature_configuration = cc_common.configure_features(
  #   ctx = ctx,
  #   cc_toolchain = cc_toolchain,
  #   requested_features = ctx.features,
  #   unsupported_features = ctx.disabled_features,
  # )

  # linker_input = cc_common.create_linker_input(
  #   owner = ctx.label,
  #   libraries = depset(direct = [
  #     cc_common.create_library_to_link(
  #       actions = ctx.actions,
  #       feature_configuration = feature_configuration,
  #       cc_toolchain = cc_toolchain,
  #       static_library = output_file,
  #     ),
  #   ]),
  # )

  # compilation_context = cc_common.create_compilation_context()

  # linking_context = cc_common.create_linking_context(
  #   linker_inputs = depset(direct = [linker_input]),
  # )

  # archiver_path = cc_common.get_tool_for_action(
  #   feature_configuration = feature_configuration,
  #   action_name = CPP_LINK_STATIC_LIBRARY_ACTION_NAME,
  # )

  # archiver_variables = cc_common.create_link_variables(
  #   feature_configuration = feature_configuration,
  #   cc_toolchain = cc_toolchain,
  #   output_file = output_file.path,
  #   is_using_linker = False,
  # )

  # command_line = cc_common.get_memory_inefficient_command_line(
  #   feature_configuration = feature_configuration,
  #   action_name = CPP_LINK_STATIC_LIBRARY_ACTION_NAME,
  #   variables = archiver_variables,
  # )

  # args = ctx.actions.args()
  # args.add_all(command_line)
  # args.add(object_file)

  # env = cc_common.get_environment_variables(
  #   feature_configuration = feature_configuration,
  #   action_name = CPP_LINK_STATIC_LIBRARY_ACTION_NAME,
  #   variables = archiver_variables,
  # )

  # ctx.actions.run(
  #   executable = archiver_path,
  #   arguments = [args],
  #   env = env,
  #   inputs = depset(
  #     direct = [object_file],
  #     transitive = [
  #       cc_toolchain.all_files,
  #     ],
  #   ),
  #   outputs = [output_file],
  # )

  # return CcInfo(
  #   compilation_context = compilation_context,
  #   linking_context = linking_context
  # )

  return [DefaultInfo(executable=out)]

alien_cc_library = rule(
  implementation = _alien_cc_library_impl,
  attrs = {
    "dep_gen": attr.label(mandatory = True, providers = [DefaultInfo]),
    # "_cc_toolchain": attr.label(
    #   default = Label("@bazel_tools//tools/cpp:current_cc_toolchain"),
    # ),
  },
  # fragments = ["cpp"],
  # toolchains = use_cpp_toolchain(),
)
