[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=462966&assignment_repo_type=GroupAssignmentRepo)
# CS178A-B-Template

## Table of Contents
- [Overview](#overview)
- [Usage](#usage)
- [How To Run](#how-to-run)
- [Diagrams](#diagrams)
- [Dependencies](#dependencies)

## Overview

The Lattice Cryptography Library provicedes a set of hardware and software tools developers can use to accelerate their Lattice-based projects.
The library primarily contains resources aimed at Lattice Cryptography, but can be generalized to be used for any Lattice-based fpa_project.


## Team
<a href="https://github.com/quartershotofespresso" target="_blank">Ratnodeep Bandyopadhyay (QuarterShotofEspresso) </a>
<a>Aaron Chen</a>
<a>Serena Lew</a>

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

