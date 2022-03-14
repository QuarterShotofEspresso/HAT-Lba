//
// Created by Ratnodeep Bandyopadhyay on 12/22/21.
//

#ifndef LATTICE_CONFIG_H
#define LATTICE_CONFIG_H

//#define DATA_TYPE double // 64-bit IEEE floating-point
//#define DATA_TYPE double

#define DATA_TYPE struct rational

// Use for Fixed-point implementations
#define RATIONAL_WIDTH 20
#define INTEGER_WIDTH 20

// Representation Selector
//#define USE_FLOATING_POINT
//#define USE_FIXED_POINT
#define USE_RATIONAL

#endif //LATTICE_CONFIG_H
