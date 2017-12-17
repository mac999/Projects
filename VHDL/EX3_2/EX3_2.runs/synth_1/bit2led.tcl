# 
# Synthesis run script generated by Vivado
# 

set_param xicom.use_bs_reader 1
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000
create_project -in_memory -part xc7z010clg400-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir D:/Project/VHDL/EX3_2/EX3_2.cache/wt [current_project]
set_property parent.project_path D:/Project/VHDL/EX3_2/EX3_2.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_output_repo d:/Project/VHDL/EX3_2/EX3_2.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_verilog -library xil_defaultlib D:/Project/VHDL/EX3_2/EX3_2.srcs/sources_1/new/bit2led.v
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc D:/Project/VHDL/EX3_2/EX3_2.srcs/constrs_1/new/EX3_2.xdc
set_property used_in_implementation false [get_files D:/Project/VHDL/EX3_2/EX3_2.srcs/constrs_1/new/EX3_2.xdc]


synth_design -top bit2led -part xc7z010clg400-1


write_checkpoint -force -noxdef bit2led.dcp

catch { report_utilization -file bit2led_utilization_synth.rpt -pb bit2led_utilization_synth.pb }
