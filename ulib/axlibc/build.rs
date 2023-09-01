fn main() {
    use std::path::{Path, PathBuf};

    fn ax_gen_c_to_rust_bindings(in_file: &str, out_file: &str) {
        println!("cargo:rerun-if-changed={in_file}");

        let allow_types = ["tm", "jmp_buf", "rlimit"];
        let allow_vars = ["RLIMIT_.*"];

        #[derive(Debug)]
        struct MyCallbacks;

        impl bindgen::callbacks::ParseCallbacks for MyCallbacks {
            fn include_file(&self, _fname: &str) {}
        }

        let mut builder = bindgen::Builder::default()
            .header(in_file)
            .clang_arg("-I./include")
            .parse_callbacks(Box::new(MyCallbacks))
            .derive_default(true)
            .size_t_is_usize(false)
            .use_core();
        for ty in allow_types {
            builder = builder.allowlist_type(ty);
        }
        for var in allow_vars {
            builder = builder.allowlist_var(var);
        }

        builder
            .generate()
            .expect("Unable to generate c->rust bindings")
            .write_to_file(out_file)
            .expect("Couldn't write bindings!");
    }

    fn gen_rust_to_c_bindings(crate_dir: &Path, out_file: &str) {
        // load configs from "cbindgen.toml"
        cbindgen::generate(crate_dir)
            .expect("Unable to generate rust->c bindings")
            .write_to_file(out_file);
    }

    let crate_dir = PathBuf::from(&std::env::var("CARGO_MANIFEST_DIR").unwrap());
    gen_rust_to_c_bindings(&crate_dir, "include_gen/axlibc.h");
    ax_gen_c_to_rust_bindings("ctypes.h", "src/libctypes_gen.rs");
}
