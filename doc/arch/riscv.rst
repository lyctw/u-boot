.. SPDX-License-Identifier: GPL-2.0+
.. Copyright (C) 2023, Yu Chien Peter Lin <peterlin@andestech.com>

RISC-V
======

Overview
--------

This document outlines the U-Boot boot process for the RISC-V architecture.
RISC-V is an open-source instruction set architecture (ISA) based on the
principles of reduced instruction set computing (RISC). It has been designed
to be flexible and customizable, allowing it to be adapted to different use
cases, from embedded systems to high performance servers.

Typical Boot Process
-----------------

RISC-V production boot images typically include a U-Boot SPL for platform-specific
initialization. The U-Boot SPL then loads a FIT image (u-boot.itb), which contains
an SBI (Supervisor Binary Interface) firmware such as `OpenSBI <https://github.com/riscv-software-src/opensbi>`_, as well as a regular
U-Boot (or U-Boot proper) running in S-mode. Finally, the S-mode Operating System
is loaded.

In between the boot stages, the hartid is passed through the a0 register, and the
start address of the devicetree is passed through the a1 register.

The following diagram illustrates the boot process::

	<----------( M-mode )--------><-------( S-mode )------>
	+------------+   +---------+    +--------+   +--------+
	| U-Boot SPL |-->|   SBI   |--->| U-Boot |-->|   OS   |
	+------------+   +---------+    +--------+   +--------+

To examine the boot process with the QEMU virt machine, you can follow the steps
in the following document:
:doc:`../board/emulation/qemu-riscv.rst`

Toolchain
---------

You can build the `RISC-V GNU toolchain <https://github.com/riscv-collab/riscv-gnu-toolchain>`_ from scratch, or download a
pre-built toolchain from the `releases page <https://github.com/riscv-collab/riscv-gnu-toolchain/releases>`_.
