# 
# Synthesis run script generated by Vivado
# 

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000
create_project -in_memory -part xc7z010clg400-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir D:/Project/VHDL/EX4_1/EX4_1.cache/wt [current_project]
set_property parent.project_path D:/Project/VHDL/EX4_1/EX4_1.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_output_repo d:/Project/VHDL/EX4_1/EX4_1.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_verilog -library xil_defaultlib {
  D:/Project/VHDL/EX4_1/EX4_1.srcs/sources_1/new/ander.v
  D:/Project/VHDL/EX4_1/EX4_1.srcs/sources_1/new/top.v
}
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc D:/Project/VHDL/EX4_1/EX4_1.srcs/constrs_2/new/EX4_1.xdc
set_property used_in_implementation false [get_files D:/Project/VHDL/EX4_1/EX4_1.srcs/constrs_2/new/EX4_1.xdc]


synth_design -top top -part xc7z010clg400-1


write_checkpoint -force -noxdef top.dcp

catch { report_utilization -file top_utilization_synth.rpt -pb top_utilization_synth.pb }
