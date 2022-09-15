# Hey Emacs, this is -*- coding: utf-8; mode: bazel -*-

def append_to_copts(kwargs, item):
  if "copts" in kwargs:
    if item not in kwargs["copts"]:
      copts = kwargs["copts"][:]
      copts.append(item)
      kwargs["copts"] = copts
  else:
    kwargs["copts"] = [item]
