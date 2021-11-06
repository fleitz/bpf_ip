# Copyright (c) PLUMgrid, Inc.
# Licensed under the Apache License, Version 2.0 (the "License")


add_executable(ip_ripper main.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-result -fPIC")