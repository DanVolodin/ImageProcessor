# Image Processor

It is a console application which enables you to apply basic filters to images.

## Supported file format

24-bit BMP images only with `DIB header` format - `BITMAPINFOHEADER`.

## Usage

Command line arguments format:

`{path to the binary file image_processor} {path to an input file} {path to an output file}
[-{filter_1 name} [filter_1 parameter_1] [filter_1 parameter_2] ...]
[-{filter_2 name} [filter_2 parameter_1] [filter_2 parameter_2] ...] ...`

Without any arguments program prints reference.

Filter list can be empty. In this case image is saved without changes.

Filters are applied successively in the given order.

### Example
`./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

Here:
1. Image from the `input.bmp` file is taken
2. Is cut to an image starting at top left pixel with size 800x600 pixels
3. Is turned to the shades of gray
4. Is blured with sigma 0.5 is applied
5. Final image is saved to the `/tmp/output.bmp` file

## Filters

### Crop (-crop width height)
Cuts an image to the given width and height from the left top corner.

If the given width or height exceed the original image size, image is not changed in this direction.

### Grayscale (-gs)
Transforms an image to the shades of gray.

### Negative (-neg)
Transforms an image to negative.

### Sharpening (-sharp)
Sharpens an image. 

### Edge Detection (-edge threshold)
Highlights the borders of an image.

After several transformations pixels with values exceeding  the `threshold` are colored to white,
the others - to black.

### Adaptive Edge Detection (-ad_edge radius)
Highlights the borders of an image. `threshold` for each pixel is counted as an average of neighbour
pixels at `radius` in the shades of gray.

Pixels with values exceeding  the `threshold` are colored to black, the others - to white.

### Gaussian Blur (-blur sigma)
Blurs an image by a Gaussian function with a given parameter `sigma`.