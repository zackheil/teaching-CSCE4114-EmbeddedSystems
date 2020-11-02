connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Arty A7-35T 210319AE169CA"} -index 0
loadhw C:/Users/zacharyheil/Desktop/embedded-systems-soc/embedded-systems-soc.sdk/system_wrapper_hw_platform_0/system.hdf
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Arty A7-35T 210319AE169CA"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Arty A7-35T 210319AE169CA"} -index 0
dow C:/Users/zacharyheil/Desktop/embedded-systems-soc/embedded-systems-soc.sdk/hello-world_bsp_xintc_tapp_example_1/Debug/hello-world_bsp_xintc_tapp_example_1.elf
bpadd -addr &main
