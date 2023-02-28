#ifndef LOADER_H
#define LOADER_H

/**
 * @brief Initialize the GUI windows.
 *
 * The width and height of the window are specified in number of cells.
 * `ICON_SIZE` is a constant determining the size in pixel of an icon.
 *
 * @param title  a string representing the title of the window
 *
 * @param width  the width of the window (number of cells)
 *
 * @param height the height of the window (number of cells)
 */
void GUI_init(char *title, int width, int height);

#endif
