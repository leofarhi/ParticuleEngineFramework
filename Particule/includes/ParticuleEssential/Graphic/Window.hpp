#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "./Color.hpp"

void CreateWindow(int width, int height, const char* title);

void DestroyWindow();

void UpdateWindow();

void ClearWindow();

void ClearWindowColor(Color color);

#endif // WINDOW_HPP