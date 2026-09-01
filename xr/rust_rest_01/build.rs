use gl_generator::{Api, Fallbacks, Profile, Registry};
use std::env;
use std::fs::File;
use std::path::Path;

fn main() {
    let dest = env::var("OUT_DIR").unwrap();
    let mut file = File::create(Path::new(&dest).join("bindings.rs")).unwrap();
    Registry::new(Api::Gl, (2, 1), Profile::Compatibility, Fallbacks::All, [])
        .write_bindings(gl_generator::StaticGenerator, &mut file)
        .unwrap();
}
