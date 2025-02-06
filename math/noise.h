#pragma once

#include <stdio.h>
#include "math_utils.h"

int noise2(int x, int y, long seed);
float noise2D(float x, float y, long seed);
float perlin2D(float x, float y, float freq, int depth, long seed);
float perlin2DOctaves(float x, float y, float freq, int depth, int octaves, int seed);