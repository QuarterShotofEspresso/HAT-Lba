[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=462966&assignment_repo_type=GroupAssignmentRepo)
# Lettuce Cryptography

## Table of Contents
- [Overview](#overview)
- [Directories](#directories)
- [Usage](#usage)
- [How To Run](#how-to-run)
- [Diagrams](#diagrams)
- [Dependencies](#dependencies)

## Overview

Lattice Cryptography algorithms are new and highly complex, and hardware that efficiently supports these algorithms has not been developed yet.  The goal of this project is to use hardware to accelerate algorithms related to lattice cryptography.  We aim to create an instruction set for a vector processor that will aid in this hardware acceleration.

Most sensitive information is secured via cryptography, and most cryptography methods are based on algebraic problems that are hard to solve.  However, with the development of Quantum Computers, encryption schemes based on arithmetic patterns such as GCD and factoring are no longer safe.  To combat this, novel encryption schemes are being devised to provide equal difficulty in cracking and ease in encryption/decryption, one of which is Lattice Cryptography.  Lattice Cryptography lies in the geometric realm rather than the algebraic realm, and is immune to the weaknesses found in algebraic encryption schemes, providing a new, harder problem to solve.

The Lattice Cryptography Library provicedes a set of hardware and software tools developers can use to accelerate their Lattice-based projects.
The library primarily contains resources aimed at Lattice Cryptography, but can be generalized to be used for any Lattice-based fpa_project.

## Directories

- `docs` - contains documentation on the math used in the lattice based functions
- `hardware` - contains the hardware implementations of our tools, more specifically the rational operations utilized in the helper functions in the `software/c_rational` directory.
- `software` - 

## Team
<a href="https://github.com/quartershotofespresso" target="_blank">Ratnodeep Bandyopadhyay (QuarterShotofEspresso) </a>
<a>Aaron Chen</a>
<a href="https://github.com/minibaguettes" target="_blank">Serena Lew (MiniBaguettes) </a>

## Usage
Demo: <https://youtu.be/JX_zPpCG1AI>


## How To Run
In the fpa_project directory, first run:

### `cd software/c_float/`

All other directories are still under development. The current working implementations of common lattice/matrix algorithms is implemented using floating-point.


### `make test_babai`

For example: `make test_babai` will build the application `test/test_babai.c`.


### `./builds/test_babai <dimension> <entry_range>`

The file produced by `make` will create an executable in the builds dir. `test_babai` accepts two parameters. The first param defines the dimension in which the lattice will
exist. The second param defines the entry range between `(0, entry_range)` of the entires in the starting matrix.


## Diagrams

[Overall System Diagram](https://drive.google.com/drive/folders/1YGCwTQlcjTE00WdZHfjSy_6PzhuNGeT6)



## Dependencies
Install GNU Compiler Collection (gcc) [Helpful Documentation](https://gcc.gnu.org/install/)

