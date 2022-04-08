	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 2	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 2	@ Tag_ABI_PCS_wchar_t
	.file	"devicetable-offsets.c"
@ GNU C89 (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.11) version 5.4.0 20160609 (arm-linux-gnueabihf)
@	compiled by GNU C version 5.4.0 20160609, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3
@ GGC heuristics: --param ggc-min-expand=98 --param ggc-min-heapsize=128558
@ options passed:  -nostdinc -I ./arch/arm/include
@ -I ./arch/arm/include/generated -I ./include -I ./arch/arm/include/uapi
@ -I ./arch/arm/include/generated/uapi -I ./include/uapi
@ -I ./include/generated/uapi -imultilib sf -imultiarch arm-linux-gnueabi
@ -D __KERNEL__ -D CC_HAVE_ASM_GOTO -D __LINUX_ARM_ARCH__=7 -U arm
@ -D KBUILD_BASENAME="devicetable_offsets"
@ -D KBUILD_MODNAME="devicetable_offsets"
@ -isystem /usr/lib/gcc/arm-linux-gnueabihf/5/include
@ -include ./include/linux/kconfig.h
@ -include ./include/linux/compiler_types.h
@ -MD scripts/mod/.devicetable-offsets.s.d
@ scripts/mod/devicetable-offsets.c -mlittle-endian -mapcs
@ -mno-sched-prolog -mabi=aapcs-linux -mfpu=vfp -marm -march=armv7-a
@ -mfloat-abi=soft -mtls-dialect=gnu
@ -auxbase-strip scripts/mod/devicetable-offsets.s -g -O2 -Wall -Wundef
@ -Wstrict-prototypes -Wno-trigraphs -Werror=implicit-function-declaration
@ -Wno-format-security -Wframe-larger-than=1024
@ -Wno-unused-but-set-variable -Wdeclaration-after-statement
@ -Wno-pointer-sign -Werror=implicit-int -Werror=strict-prototypes
@ -Werror=date-time -Werror=incompatible-pointer-types
@ -Werror=designated-init -std=gnu90 -p -fno-strict-aliasing -fno-common
@ -fshort-wchar -fno-PIE -fno-dwarf2-cfi-asm -fno-ipa-sra -funwind-tables
@ -fno-delete-null-pointer-checks -fstack-protector-strong
@ -fno-omit-frame-pointer -fno-optimize-sibling-calls
@ -fno-var-tracking-assignments -fno-strict-overflow
@ -fno-merge-all-constants -fmerge-constants -fstack-check=no
@ -fconserve-stack -fverbose-asm --param allow-store-data-races=0
@ -fstack-protector-strong
@ options enabled:  -faggressive-loop-optimizations -falign-functions
@ -falign-jumps -falign-labels -falign-loops -fauto-inc-dec
@ -fbranch-count-reg -fcaller-saves -fchkp-check-incomplete-type
@ -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
@ -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
@ -fchkp-use-static-bounds -fchkp-use-static-const-bounds
@ -fchkp-use-wrappers -fcombine-stack-adjustments -fcompare-elim
@ -fcprop-registers -fcrossjumping -fcse-follow-jumps -fdefer-pop
@ -fdevirtualize -fdevirtualize-speculatively -fearly-inlining
@ -feliminate-unused-debug-types -fexpensive-optimizations
@ -fforward-propagate -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime
@ -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads -fident
@ -fif-conversion -fif-conversion2 -findirect-inlining -finline
@ -finline-atomics -finline-functions-called-once -finline-small-functions
@ -fipa-cp -fipa-cp-alignment -fipa-icf -fipa-icf-functions
@ -fipa-icf-variables -fipa-profile -fipa-pure-const -fipa-reference
@ -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
@ -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
@ -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
@ -fmath-errno -fmerge-constants -fmerge-debug-strings
@ -fmove-loop-invariants -foptimize-strlen -fpartial-inlining -fpeephole
@ -fpeephole2 -fplt -fprefetch-loop-arrays -fprofile -freg-struct-return
@ -freorder-blocks -freorder-functions -frerun-cse-after-loop
@ -fsched-critical-path-heuristic -fsched-dep-count-heuristic
@ -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
@ -fsched-pressure -fsched-rank-heuristic -fsched-spec
@ -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-insns
@ -fschedule-insns2 -fsection-anchors -fsemantic-interposition
@ -fshow-column -fsigned-zeros -fsplit-ivs-in-unroller -fsplit-wide-types
@ -fssa-phiopt -fstack-protector-strong -fstdarg-opt
@ -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
@ -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
@ -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop
@ -ftree-copyrename -ftree-cselim -ftree-dce -ftree-dominator-opts
@ -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
@ -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
@ -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
@ -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
@ -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
@ -funit-at-a-time -funwind-tables -fvar-tracking -fverbose-asm
@ -fzero-initialized-in-bss -mapcs-frame -marm -mglibc -mlittle-endian
@ -mpic-data-is-text-relative -munaligned-access -mvectorize-with-neon-quad

	.text
.Ltext0:
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	.fnstart
.LFB26:
	.file 1 "scripts/mod/devicetable-offsets.c"
	.loc 1 10 0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.movsp ip
	mov	ip, sp	@,
.LCFI0:
	push	{fp, ip, lr, pc}	@
	.pad #4
	.save {fp, ip, lr}
.LCFI1:
	.setfp fp, ip, #-4
	sub	fp, ip, #4	@,,
.LCFI2:
	push	{lr}
	bl	__gnu_mcount_nc
	.loc 1 10 0
	.loc 1 11 0
	.syntax divided
@ 11 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_usb_device_id #24 sizeof(struct usb_device_id)"	@
@ 0 "" 2
	.loc 1 12 0
@ 12 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_match_flags #0 offsetof(struct usb_device_id, match_flags)"	@
@ 0 "" 2
	.loc 1 13 0
@ 13 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_idVendor #2 offsetof(struct usb_device_id, idVendor)"	@
@ 0 "" 2
	.loc 1 14 0
@ 14 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_idProduct #4 offsetof(struct usb_device_id, idProduct)"	@
@ 0 "" 2
	.loc 1 15 0
@ 15 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bcdDevice_lo #6 offsetof(struct usb_device_id, bcdDevice_lo)"	@
@ 0 "" 2
	.loc 1 16 0
@ 16 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bcdDevice_hi #8 offsetof(struct usb_device_id, bcdDevice_hi)"	@
@ 0 "" 2
	.loc 1 17 0
@ 17 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bDeviceClass #10 offsetof(struct usb_device_id, bDeviceClass)"	@
@ 0 "" 2
	.loc 1 18 0
@ 18 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bDeviceSubClass #11 offsetof(struct usb_device_id, bDeviceSubClass)"	@
@ 0 "" 2
	.loc 1 19 0
@ 19 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bDeviceProtocol #12 offsetof(struct usb_device_id, bDeviceProtocol)"	@
@ 0 "" 2
	.loc 1 20 0
@ 20 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bInterfaceClass #13 offsetof(struct usb_device_id, bInterfaceClass)"	@
@ 0 "" 2
	.loc 1 21 0
@ 21 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bInterfaceSubClass #14 offsetof(struct usb_device_id, bInterfaceSubClass)"	@
@ 0 "" 2
	.loc 1 22 0
@ 22 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bInterfaceProtocol #15 offsetof(struct usb_device_id, bInterfaceProtocol)"	@
@ 0 "" 2
	.loc 1 23 0
@ 23 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_usb_device_id_bInterfaceNumber #16 offsetof(struct usb_device_id, bInterfaceNumber)"	@
@ 0 "" 2
	.loc 1 25 0
@ 25 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_hid_device_id #16 sizeof(struct hid_device_id)"	@
@ 0 "" 2
	.loc 1 26 0
@ 26 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hid_device_id_bus #0 offsetof(struct hid_device_id, bus)"	@
@ 0 "" 2
	.loc 1 27 0
@ 27 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hid_device_id_group #2 offsetof(struct hid_device_id, group)"	@
@ 0 "" 2
	.loc 1 28 0
@ 28 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hid_device_id_vendor #4 offsetof(struct hid_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 29 0
@ 29 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hid_device_id_product #8 offsetof(struct hid_device_id, product)"	@
@ 0 "" 2
	.loc 1 31 0
@ 31 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_ieee1394_device_id #24 sizeof(struct ieee1394_device_id)"	@
@ 0 "" 2
	.loc 1 32 0
@ 32 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ieee1394_device_id_match_flags #0 offsetof(struct ieee1394_device_id, match_flags)"	@
@ 0 "" 2
	.loc 1 33 0
@ 33 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ieee1394_device_id_vendor_id #4 offsetof(struct ieee1394_device_id, vendor_id)"	@
@ 0 "" 2
	.loc 1 34 0
@ 34 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ieee1394_device_id_model_id #8 offsetof(struct ieee1394_device_id, model_id)"	@
@ 0 "" 2
	.loc 1 35 0
@ 35 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ieee1394_device_id_specifier_id #12 offsetof(struct ieee1394_device_id, specifier_id)"	@
@ 0 "" 2
	.loc 1 36 0
@ 36 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ieee1394_device_id_version #16 offsetof(struct ieee1394_device_id, version)"	@
@ 0 "" 2
	.loc 1 38 0
@ 38 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_pci_device_id #28 sizeof(struct pci_device_id)"	@
@ 0 "" 2
	.loc 1 39 0
@ 39 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pci_device_id_vendor #0 offsetof(struct pci_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 40 0
@ 40 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pci_device_id_device #4 offsetof(struct pci_device_id, device)"	@
@ 0 "" 2
	.loc 1 41 0
@ 41 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pci_device_id_subvendor #8 offsetof(struct pci_device_id, subvendor)"	@
@ 0 "" 2
	.loc 1 42 0
@ 42 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pci_device_id_subdevice #12 offsetof(struct pci_device_id, subdevice)"	@
@ 0 "" 2
	.loc 1 43 0
@ 43 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pci_device_id_class #16 offsetof(struct pci_device_id, class)"	@
@ 0 "" 2
	.loc 1 44 0
@ 44 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pci_device_id_class_mask #20 offsetof(struct pci_device_id, class_mask)"	@
@ 0 "" 2
	.loc 1 46 0
@ 46 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_ccw_device_id #12 sizeof(struct ccw_device_id)"	@
@ 0 "" 2
	.loc 1 47 0
@ 47 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ccw_device_id_match_flags #0 offsetof(struct ccw_device_id, match_flags)"	@
@ 0 "" 2
	.loc 1 48 0
@ 48 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ccw_device_id_cu_type #2 offsetof(struct ccw_device_id, cu_type)"	@
@ 0 "" 2
	.loc 1 49 0
@ 49 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ccw_device_id_cu_model #6 offsetof(struct ccw_device_id, cu_model)"	@
@ 0 "" 2
	.loc 1 50 0
@ 50 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ccw_device_id_dev_type #4 offsetof(struct ccw_device_id, dev_type)"	@
@ 0 "" 2
	.loc 1 51 0
@ 51 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ccw_device_id_dev_model #7 offsetof(struct ccw_device_id, dev_model)"	@
@ 0 "" 2
	.loc 1 53 0
@ 53 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_ap_device_id #8 sizeof(struct ap_device_id)"	@
@ 0 "" 2
	.loc 1 54 0
@ 54 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ap_device_id_dev_type #2 offsetof(struct ap_device_id, dev_type)"	@
@ 0 "" 2
	.loc 1 56 0
@ 56 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_css_device_id #8 sizeof(struct css_device_id)"	@
@ 0 "" 2
	.loc 1 57 0
@ 57 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_css_device_id_type #1 offsetof(struct css_device_id, type)"	@
@ 0 "" 2
	.loc 1 59 0
@ 59 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_serio_device_id #4 sizeof(struct serio_device_id)"	@
@ 0 "" 2
	.loc 1 60 0
@ 60 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_serio_device_id_type #0 offsetof(struct serio_device_id, type)"	@
@ 0 "" 2
	.loc 1 61 0
@ 61 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_serio_device_id_proto #3 offsetof(struct serio_device_id, proto)"	@
@ 0 "" 2
	.loc 1 62 0
@ 62 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_serio_device_id_id #2 offsetof(struct serio_device_id, id)"	@
@ 0 "" 2
	.loc 1 63 0
@ 63 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_serio_device_id_extra #1 offsetof(struct serio_device_id, extra)"	@
@ 0 "" 2
	.loc 1 65 0
@ 65 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_acpi_device_id #24 sizeof(struct acpi_device_id)"	@
@ 0 "" 2
	.loc 1 66 0
@ 66 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_acpi_device_id_id #0 offsetof(struct acpi_device_id, id)"	@
@ 0 "" 2
	.loc 1 67 0
@ 67 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_acpi_device_id_cls #16 offsetof(struct acpi_device_id, cls)"	@
@ 0 "" 2
	.loc 1 68 0
@ 68 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_acpi_device_id_cls_msk #20 offsetof(struct acpi_device_id, cls_msk)"	@
@ 0 "" 2
	.loc 1 70 0
@ 70 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_pnp_device_id #12 sizeof(struct pnp_device_id)"	@
@ 0 "" 2
	.loc 1 71 0
@ 71 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pnp_device_id_id #0 offsetof(struct pnp_device_id, id)"	@
@ 0 "" 2
	.loc 1 73 0
@ 73 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_pnp_card_device_id #76 sizeof(struct pnp_card_device_id)"	@
@ 0 "" 2
	.loc 1 74 0
@ 74 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pnp_card_device_id_devs #12 offsetof(struct pnp_card_device_id, devs)"	@
@ 0 "" 2
	.loc 1 76 0
@ 76 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_pcmcia_device_id #52 sizeof(struct pcmcia_device_id)"	@
@ 0 "" 2
	.loc 1 77 0
@ 77 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pcmcia_device_id_match_flags #0 offsetof(struct pcmcia_device_id, match_flags)"	@
@ 0 "" 2
	.loc 1 78 0
@ 78 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pcmcia_device_id_manf_id #2 offsetof(struct pcmcia_device_id, manf_id)"	@
@ 0 "" 2
	.loc 1 79 0
@ 79 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pcmcia_device_id_card_id #4 offsetof(struct pcmcia_device_id, card_id)"	@
@ 0 "" 2
	.loc 1 80 0
@ 80 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pcmcia_device_id_func_id #6 offsetof(struct pcmcia_device_id, func_id)"	@
@ 0 "" 2
	.loc 1 81 0
@ 81 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pcmcia_device_id_function #7 offsetof(struct pcmcia_device_id, function)"	@
@ 0 "" 2
	.loc 1 82 0
@ 82 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pcmcia_device_id_device_no #8 offsetof(struct pcmcia_device_id, device_no)"	@
@ 0 "" 2
	.loc 1 83 0
@ 83 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_pcmcia_device_id_prod_id_hash #12 offsetof(struct pcmcia_device_id, prod_id_hash)"	@
@ 0 "" 2
	.loc 1 85 0
@ 85 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_of_device_id #196 sizeof(struct of_device_id)"	@
@ 0 "" 2
	.loc 1 86 0
@ 86 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_of_device_id_name #0 offsetof(struct of_device_id, name)"	@
@ 0 "" 2
	.loc 1 87 0
@ 87 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_of_device_id_type #32 offsetof(struct of_device_id, type)"	@
@ 0 "" 2
	.loc 1 88 0
@ 88 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_of_device_id_compatible #64 offsetof(struct of_device_id, compatible)"	@
@ 0 "" 2
	.loc 1 90 0
@ 90 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_vio_device_id #64 sizeof(struct vio_device_id)"	@
@ 0 "" 2
	.loc 1 91 0
@ 91 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_vio_device_id_type #0 offsetof(struct vio_device_id, type)"	@
@ 0 "" 2
	.loc 1 92 0
@ 92 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_vio_device_id_compat #32 offsetof(struct vio_device_id, compat)"	@
@ 0 "" 2
	.loc 1 94 0
@ 94 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_input_device_id #164 sizeof(struct input_device_id)"	@
@ 0 "" 2
	.loc 1 95 0
@ 95 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_flags #0 offsetof(struct input_device_id, flags)"	@
@ 0 "" 2
	.loc 1 96 0
@ 96 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_bustype #4 offsetof(struct input_device_id, bustype)"	@
@ 0 "" 2
	.loc 1 97 0
@ 97 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_vendor #6 offsetof(struct input_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 98 0
@ 98 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_product #8 offsetof(struct input_device_id, product)"	@
@ 0 "" 2
	.loc 1 99 0
@ 99 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_version #10 offsetof(struct input_device_id, version)"	@
@ 0 "" 2
	.loc 1 100 0
@ 100 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_evbit #12 offsetof(struct input_device_id, evbit)"	@
@ 0 "" 2
	.loc 1 101 0
@ 101 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_keybit #16 offsetof(struct input_device_id, keybit)"	@
@ 0 "" 2
	.loc 1 102 0
@ 102 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_relbit #112 offsetof(struct input_device_id, relbit)"	@
@ 0 "" 2
	.loc 1 103 0
@ 103 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_absbit #116 offsetof(struct input_device_id, absbit)"	@
@ 0 "" 2
	.loc 1 104 0
@ 104 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_mscbit #124 offsetof(struct input_device_id, mscbit)"	@
@ 0 "" 2
	.loc 1 105 0
@ 105 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_ledbit #128 offsetof(struct input_device_id, ledbit)"	@
@ 0 "" 2
	.loc 1 106 0
@ 106 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_sndbit #132 offsetof(struct input_device_id, sndbit)"	@
@ 0 "" 2
	.loc 1 107 0
@ 107 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_ffbit #136 offsetof(struct input_device_id, ffbit)"	@
@ 0 "" 2
	.loc 1 108 0
@ 108 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_input_device_id_swbit #152 offsetof(struct input_device_id, swbit)"	@
@ 0 "" 2
	.loc 1 110 0
@ 110 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_eisa_device_id #12 sizeof(struct eisa_device_id)"	@
@ 0 "" 2
	.loc 1 111 0
@ 111 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_eisa_device_id_sig #0 offsetof(struct eisa_device_id, sig)"	@
@ 0 "" 2
	.loc 1 113 0
@ 113 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_parisc_device_id #8 sizeof(struct parisc_device_id)"	@
@ 0 "" 2
	.loc 1 114 0
@ 114 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_parisc_device_id_hw_type #0 offsetof(struct parisc_device_id, hw_type)"	@
@ 0 "" 2
	.loc 1 115 0
@ 115 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_parisc_device_id_hversion #2 offsetof(struct parisc_device_id, hversion)"	@
@ 0 "" 2
	.loc 1 116 0
@ 116 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_parisc_device_id_hversion_rev #1 offsetof(struct parisc_device_id, hversion_rev)"	@
@ 0 "" 2
	.loc 1 117 0
@ 117 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_parisc_device_id_sversion #4 offsetof(struct parisc_device_id, sversion)"	@
@ 0 "" 2
	.loc 1 119 0
@ 119 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_sdio_device_id #12 sizeof(struct sdio_device_id)"	@
@ 0 "" 2
	.loc 1 120 0
@ 120 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_sdio_device_id_class #0 offsetof(struct sdio_device_id, class)"	@
@ 0 "" 2
	.loc 1 121 0
@ 121 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_sdio_device_id_vendor #2 offsetof(struct sdio_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 122 0
@ 122 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_sdio_device_id_device #4 offsetof(struct sdio_device_id, device)"	@
@ 0 "" 2
	.loc 1 124 0
@ 124 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_ssb_device_id #6 sizeof(struct ssb_device_id)"	@
@ 0 "" 2
	.loc 1 125 0
@ 125 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ssb_device_id_vendor #0 offsetof(struct ssb_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 126 0
@ 126 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ssb_device_id_coreid #2 offsetof(struct ssb_device_id, coreid)"	@
@ 0 "" 2
	.loc 1 127 0
@ 127 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ssb_device_id_revision #4 offsetof(struct ssb_device_id, revision)"	@
@ 0 "" 2
	.loc 1 129 0
@ 129 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_bcma_device_id #6 sizeof(struct bcma_device_id)"	@
@ 0 "" 2
	.loc 1 130 0
@ 130 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_bcma_device_id_manuf #0 offsetof(struct bcma_device_id, manuf)"	@
@ 0 "" 2
	.loc 1 131 0
@ 131 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_bcma_device_id_id #2 offsetof(struct bcma_device_id, id)"	@
@ 0 "" 2
	.loc 1 132 0
@ 132 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_bcma_device_id_rev #4 offsetof(struct bcma_device_id, rev)"	@
@ 0 "" 2
	.loc 1 133 0
@ 133 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_bcma_device_id_class #5 offsetof(struct bcma_device_id, class)"	@
@ 0 "" 2
	.loc 1 135 0
@ 135 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_virtio_device_id #8 sizeof(struct virtio_device_id)"	@
@ 0 "" 2
	.loc 1 136 0
@ 136 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_virtio_device_id_device #0 offsetof(struct virtio_device_id, device)"	@
@ 0 "" 2
	.loc 1 137 0
@ 137 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_virtio_device_id_vendor #4 offsetof(struct virtio_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 139 0
@ 139 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_hv_vmbus_device_id #20 sizeof(struct hv_vmbus_device_id)"	@
@ 0 "" 2
	.loc 1 140 0
@ 140 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hv_vmbus_device_id_guid #0 offsetof(struct hv_vmbus_device_id, guid)"	@
@ 0 "" 2
	.loc 1 142 0
@ 142 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_rpmsg_device_id #32 sizeof(struct rpmsg_device_id)"	@
@ 0 "" 2
	.loc 1 143 0
@ 143 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_rpmsg_device_id_name #0 offsetof(struct rpmsg_device_id, name)"	@
@ 0 "" 2
	.loc 1 145 0
@ 145 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_i2c_device_id #24 sizeof(struct i2c_device_id)"	@
@ 0 "" 2
	.loc 1 146 0
@ 146 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_i2c_device_id_name #0 offsetof(struct i2c_device_id, name)"	@
@ 0 "" 2
	.loc 1 148 0
@ 148 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_spi_device_id #36 sizeof(struct spi_device_id)"	@
@ 0 "" 2
	.loc 1 149 0
@ 149 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_spi_device_id_name #0 offsetof(struct spi_device_id, name)"	@
@ 0 "" 2
	.loc 1 151 0
@ 151 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_dmi_system_id #332 sizeof(struct dmi_system_id)"	@
@ 0 "" 2
	.loc 1 152 0
@ 152 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_dmi_system_id_matches #8 offsetof(struct dmi_system_id, matches)"	@
@ 0 "" 2
	.loc 1 154 0
@ 154 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_platform_device_id #24 sizeof(struct platform_device_id)"	@
@ 0 "" 2
	.loc 1 155 0
@ 155 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_platform_device_id_name #0 offsetof(struct platform_device_id, name)"	@
@ 0 "" 2
	.loc 1 157 0
@ 157 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_mdio_device_id #8 sizeof(struct mdio_device_id)"	@
@ 0 "" 2
	.loc 1 158 0
@ 158 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_mdio_device_id_phy_id #0 offsetof(struct mdio_device_id, phy_id)"	@
@ 0 "" 2
	.loc 1 159 0
@ 159 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_mdio_device_id_phy_id_mask #4 offsetof(struct mdio_device_id, phy_id_mask)"	@
@ 0 "" 2
	.loc 1 161 0
@ 161 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_zorro_device_id #8 sizeof(struct zorro_device_id)"	@
@ 0 "" 2
	.loc 1 162 0
@ 162 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_zorro_device_id_id #0 offsetof(struct zorro_device_id, id)"	@
@ 0 "" 2
	.loc 1 164 0
@ 164 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_isapnp_device_id #12 sizeof(struct isapnp_device_id)"	@
@ 0 "" 2
	.loc 1 165 0
@ 165 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_isapnp_device_id_vendor #4 offsetof(struct isapnp_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 166 0
@ 166 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_isapnp_device_id_function #6 offsetof(struct isapnp_device_id, function)"	@
@ 0 "" 2
	.loc 1 168 0
@ 168 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_ipack_device_id #12 sizeof(struct ipack_device_id)"	@
@ 0 "" 2
	.loc 1 169 0
@ 169 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ipack_device_id_format #0 offsetof(struct ipack_device_id, format)"	@
@ 0 "" 2
	.loc 1 170 0
@ 170 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ipack_device_id_vendor #4 offsetof(struct ipack_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 171 0
@ 171 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ipack_device_id_device #8 offsetof(struct ipack_device_id, device)"	@
@ 0 "" 2
	.loc 1 173 0
@ 173 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_amba_id #12 sizeof(struct amba_id)"	@
@ 0 "" 2
	.loc 1 174 0
@ 174 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_amba_id_id #0 offsetof(struct amba_id, id)"	@
@ 0 "" 2
	.loc 1 175 0
@ 175 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_amba_id_mask #4 offsetof(struct amba_id, mask)"	@
@ 0 "" 2
	.loc 1 177 0
@ 177 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_mips_cdmm_device_id #1 sizeof(struct mips_cdmm_device_id)"	@
@ 0 "" 2
	.loc 1 178 0
@ 178 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_mips_cdmm_device_id_type #0 offsetof(struct mips_cdmm_device_id, type)"	@
@ 0 "" 2
	.loc 1 180 0
@ 180 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_x86_cpu_id #12 sizeof(struct x86_cpu_id)"	@
@ 0 "" 2
	.loc 1 181 0
@ 181 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_x86_cpu_id_feature #6 offsetof(struct x86_cpu_id, feature)"	@
@ 0 "" 2
	.loc 1 182 0
@ 182 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_x86_cpu_id_family #2 offsetof(struct x86_cpu_id, family)"	@
@ 0 "" 2
	.loc 1 183 0
@ 183 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_x86_cpu_id_model #4 offsetof(struct x86_cpu_id, model)"	@
@ 0 "" 2
	.loc 1 184 0
@ 184 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_x86_cpu_id_vendor #0 offsetof(struct x86_cpu_id, vendor)"	@
@ 0 "" 2
	.loc 1 186 0
@ 186 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_cpu_feature #2 sizeof(struct cpu_feature)"	@
@ 0 "" 2
	.loc 1 187 0
@ 187 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_cpu_feature_feature #0 offsetof(struct cpu_feature, feature)"	@
@ 0 "" 2
	.loc 1 189 0
@ 189 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_mei_cl_device_id #56 sizeof(struct mei_cl_device_id)"	@
@ 0 "" 2
	.loc 1 190 0
@ 190 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_mei_cl_device_id_name #0 offsetof(struct mei_cl_device_id, name)"	@
@ 0 "" 2
	.loc 1 191 0
@ 191 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_mei_cl_device_id_uuid #32 offsetof(struct mei_cl_device_id, uuid)"	@
@ 0 "" 2
	.loc 1 192 0
@ 192 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_mei_cl_device_id_version #48 offsetof(struct mei_cl_device_id, version)"	@
@ 0 "" 2
	.loc 1 194 0
@ 194 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_rio_device_id #8 sizeof(struct rio_device_id)"	@
@ 0 "" 2
	.loc 1 195 0
@ 195 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_rio_device_id_did #0 offsetof(struct rio_device_id, did)"	@
@ 0 "" 2
	.loc 1 196 0
@ 196 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_rio_device_id_vid #2 offsetof(struct rio_device_id, vid)"	@
@ 0 "" 2
	.loc 1 197 0
@ 197 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_rio_device_id_asm_did #4 offsetof(struct rio_device_id, asm_did)"	@
@ 0 "" 2
	.loc 1 198 0
@ 198 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_rio_device_id_asm_vid #6 offsetof(struct rio_device_id, asm_vid)"	@
@ 0 "" 2
	.loc 1 200 0
@ 200 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_ulpi_device_id #8 sizeof(struct ulpi_device_id)"	@
@ 0 "" 2
	.loc 1 201 0
@ 201 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ulpi_device_id_vendor #0 offsetof(struct ulpi_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 202 0
@ 202 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_ulpi_device_id_product #2 offsetof(struct ulpi_device_id, product)"	@
@ 0 "" 2
	.loc 1 204 0
@ 204 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_hda_device_id #20 sizeof(struct hda_device_id)"	@
@ 0 "" 2
	.loc 1 205 0
@ 205 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hda_device_id_vendor_id #0 offsetof(struct hda_device_id, vendor_id)"	@
@ 0 "" 2
	.loc 1 206 0
@ 206 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hda_device_id_rev_id #4 offsetof(struct hda_device_id, rev_id)"	@
@ 0 "" 2
	.loc 1 207 0
@ 207 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_hda_device_id_api_version #8 offsetof(struct hda_device_id, api_version)"	@
@ 0 "" 2
	.loc 1 209 0
@ 209 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_sdw_device_id #8 sizeof(struct sdw_device_id)"	@
@ 0 "" 2
	.loc 1 210 0
@ 210 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_sdw_device_id_mfg_id #0 offsetof(struct sdw_device_id, mfg_id)"	@
@ 0 "" 2
	.loc 1 211 0
@ 211 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_sdw_device_id_part_id #2 offsetof(struct sdw_device_id, part_id)"	@
@ 0 "" 2
	.loc 1 213 0
@ 213 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_fsl_mc_device_id #18 sizeof(struct fsl_mc_device_id)"	@
@ 0 "" 2
	.loc 1 214 0
@ 214 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_fsl_mc_device_id_vendor #0 offsetof(struct fsl_mc_device_id, vendor)"	@
@ 0 "" 2
	.loc 1 215 0
@ 215 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_fsl_mc_device_id_obj_type #2 offsetof(struct fsl_mc_device_id, obj_type)"	@
@ 0 "" 2
	.loc 1 217 0
@ 217 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_tb_service_id #32 sizeof(struct tb_service_id)"	@
@ 0 "" 2
	.loc 1 218 0
@ 218 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_tb_service_id_match_flags #0 offsetof(struct tb_service_id, match_flags)"	@
@ 0 "" 2
	.loc 1 219 0
@ 219 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_tb_service_id_protocol_key #4 offsetof(struct tb_service_id, protocol_key)"	@
@ 0 "" 2
	.loc 1 220 0
@ 220 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_tb_service_id_protocol_id #16 offsetof(struct tb_service_id, protocol_id)"	@
@ 0 "" 2
	.loc 1 221 0
@ 221 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_tb_service_id_protocol_version #20 offsetof(struct tb_service_id, protocol_version)"	@
@ 0 "" 2
	.loc 1 222 0
@ 222 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_tb_service_id_protocol_revision #24 offsetof(struct tb_service_id, protocol_revision)"	@
@ 0 "" 2
	.loc 1 224 0
@ 224 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->SIZE_typec_device_id #8 sizeof(struct typec_device_id)"	@
@ 0 "" 2
	.loc 1 225 0
@ 225 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_typec_device_id_svid #0 offsetof(struct typec_device_id, svid)"	@
@ 0 "" 2
	.loc 1 226 0
@ 226 "scripts/mod/devicetable-offsets.c" 1
	
.ascii "->OFF_typec_device_id_mode #2 offsetof(struct typec_device_id, mode)"	@
@ 0 "" 2
	.loc 1 229 0
	.arm
	.syntax unified
	mov	r0, #0	@,
	ldmfd	sp, {fp, sp, pc}	@
.LFE26:
	.fnend
	.size	main, .-main
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.byte	0x4
	.4byte	.LCFI0-.LFB26
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x8b
	.uleb128 0x4
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8e
	.uleb128 0x2
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
	.text
.Letext0:
	.file 2 "./include/uapi/asm-generic/int-ll64.h"
	.file 3 "./include/uapi/linux/uuid.h"
	.file 4 "./include/linux/uuid.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x109
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x1
	.4byte	.LASF18
	.4byte	.LASF19
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x2
	.byte	0x15
	.4byte	0x53
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF11
	.uleb128 0x5
	.byte	0x10
	.byte	0x3
	.byte	0x17
	.4byte	0x9e
	.uleb128 0x6
	.ascii	"b\000"
	.byte	0x3
	.byte	0x18
	.4byte	0x9e
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	0x48
	.4byte	0xae
	.uleb128 0x8
	.4byte	0x2c
	.byte	0xf
	.byte	0
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x3
	.byte	0x19
	.4byte	0x8b
	.uleb128 0x5
	.byte	0x10
	.byte	0x4
	.byte	0x18
	.4byte	0xcc
	.uleb128 0x6
	.ascii	"b\000"
	.byte	0x4
	.byte	0x19
	.4byte	0x9e
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x4
	.byte	0x1a
	.4byte	0xb9
	.uleb128 0x9
	.4byte	.LASF20
	.byte	0x1
	.byte	0x9
	.4byte	0x68
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xa
	.4byte	.LASF15
	.byte	0x4
	.byte	0x29
	.4byte	0xf7
	.uleb128 0xb
	.4byte	0xae
	.uleb128 0xa
	.4byte	.LASF16
	.byte	0x4
	.byte	0x2a
	.4byte	0x107
	.uleb128 0xb
	.4byte	0xcc
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB26
	.4byte	.LFE26
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF8:
	.ascii	"long long int\000"
.LASF12:
	.ascii	"__u8\000"
.LASF3:
	.ascii	"unsigned int\000"
.LASF20:
	.ascii	"main\000"
.LASF14:
	.ascii	"uuid_t\000"
.LASF13:
	.ascii	"guid_t\000"
.LASF0:
	.ascii	"long unsigned int\000"
.LASF9:
	.ascii	"long long unsigned int\000"
.LASF15:
	.ascii	"guid_null\000"
.LASF17:
	.ascii	"GNU C89 5.4.0 20160609 -mlittle-endian -mapcs -mno-"
	.ascii	"sched-prolog -mabi=aapcs-linux -mfpu=vfp -marm -mar"
	.ascii	"ch=armv7-a -mfloat-abi=soft -mtls-dialect=gnu -g -O"
	.ascii	"2 -std=gnu90 -p -fno-strict-aliasing -fno-common -f"
	.ascii	"short-wchar -fno-PIE -fno-dwarf2-cfi-asm -fno-ipa-s"
	.ascii	"ra -funwind-tables -fno-delete-null-pointer-checks "
	.ascii	"-fstack-protector-strong -fno-omit-frame-pointer -f"
	.ascii	"no-optimize-sibling-calls -fno-var-tracking-assignm"
	.ascii	"ents -fno-strict-overflow -fno-merge-all-constants "
	.ascii	"-fmerge-constants -fstack-check=no -fconserve-stack"
	.ascii	" --param allow-store-data-races=0 -fstack-protector"
	.ascii	"-strong\000"
.LASF16:
	.ascii	"uuid_null\000"
.LASF5:
	.ascii	"unsigned char\000"
.LASF2:
	.ascii	"char\000"
.LASF19:
	.ascii	"/usr/src/linux-headers-4.19.0\000"
.LASF10:
	.ascii	"long int\000"
.LASF11:
	.ascii	"_Bool\000"
.LASF7:
	.ascii	"short unsigned int\000"
.LASF4:
	.ascii	"signed char\000"
.LASF18:
	.ascii	"scripts/mod/devicetable-offsets.c\000"
.LASF6:
	.ascii	"short int\000"
.LASF1:
	.ascii	"sizetype\000"
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits
