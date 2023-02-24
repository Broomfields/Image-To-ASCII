# ImageToASCII - A program to convert an image to ASCII and export it to a text file.

## Command Line Parameters

1. The first parameter, `image_file`, is a string representing the path to the image file.

   - The file type must be one of the following:
     - PNG
     - JPG, JPEG
     - BMP
     - GIF
     - TIFF
     - The following could be supported in the future? {PSD, PDN, AVIF, WebP, SVG, HEIC, ICO, or DDS}.
   - The program must assert that the `image_file` is a valid path to an accepted image file. If not, the program must exit.
2. The second parameter, `export_dir`, is a string representing the path to the directory to export the ASCII conversion.

   - The program must assert that the `export_dir` is a valid directory path.
   - If the directory does not exist but is a valid path, the program must create the directory.
   - If the directory is invalid, the program must exit.

## Process

1. Verify that both parameters, `image_file` and `export_dir`, are valid.
2. Convert the image file to ASCII.
3. Export the ASCII conversion to a text file with the following format:

   - The file name must start with the string literal "Exported ASCII - "
   - The file name must end with the date and time of the export.
   - The file must be saved in the `export_dir` directory.
4. If the program encounters any errors during the conversion process, an error log must be created instead of the ASCII text file.

   - The error log must be a csv file.
   - The file name must start with the string literal "ASCII Error Log - "
   - The file name must end with the date and time of the error.
   - The error log must contain the following fields with headers:
     - Date and time
     - Image file path
     - Export directory path
     - Reason for error (e.g., invalid parameters, exception message)
   - The error log must be saved in the `export_dir` directory.
