use std::error::Error;
use std::fs::{create_dir_all, File};
use std::path::Path;
use std::time::{SystemTime, UNIX_EPOCH};

// Function to convert the image to ASCII
fn image_to_ascii(image_file: &str, export_dir: &str) -> Result<(), Box<dyn Error>> {
    // Verify that both parameters are valid
    if !Path::new(image_file).is_file() {
        return Err(From::from("The image file is not valid"));
    }
    if !Path::new(export_dir).is_dir() {
        match create_dir_all(export_dir) {
            Ok(_) => (),
            Err(e) => return Err(From::from(e)),
        }
    }

    // Perform ASCII conversion here
    // TODO

    // Export the ASCII conversion to a text file
    let time = SystemTime::now().duration_since(UNIX_EPOCH)?;
    let filename = format!("{}/Exported ASCII - {}", export_dir, time.as_millis());
    let file = File::create(filename)?;

    Ok(())
}

// Function to create an error log
fn create_error_log(export_dir: &str, error_message: &str) {
    let time = SystemTime::now().duration_since(UNIX_EPOCH).unwrap();
    let filename = format!("{}/ASCII Error Log - {}.csv", export_dir, time.as_millis());
    let file = File::create(filename).unwrap();

    // Write the error log contents here
    // TODO
}

fn main() {
    let image_file = "path/to/image";
    let export_dir = "path/to/export_dir";

    match image_to_ascii(image_file, export_dir) {
        Ok(_) => (),
        Err(e) => {
            create_error_log(export_dir, &e.to_string());
            println!("{}", e);
        }
    }
}
