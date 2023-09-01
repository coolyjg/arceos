fn main() {
    use std::path::{Path, PathBuf};

    fn gen_rust_to_c_bindings(crate_dir: &Path, out_file: &str) {
        // load configs from "cbindgen.toml"
        cbindgen::generate(crate_dir)
            .expect("Unable to generate rust->c bindings")
            .write_to_file(out_file);
    }

    let crate_dir = PathBuf::from(&std::env::var("CARGO_MANIFEST_DIR").unwrap());
    gen_rust_to_c_bindings(&crate_dir, "include_gen/axlibc.h");
}
