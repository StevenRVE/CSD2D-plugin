cmake_minimum_required(VERSION 3.7)
 project(sve-chorus)

 add_subdirectory(dpf)

 dpf_add_plugin(sve-chorus
   TARGETS clap lv2 vst2 vst3

   FILES_DSP
       source/chorus.cpp
 )

 target_include_directories(sve-chorus
   PUBLIC source)

 target_compile_options(sve-chorus PUBLIC "-Wno-c++11-narrowing")

 add_compile_options(-fdiagnostics-color=always)