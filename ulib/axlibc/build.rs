fn main() {
    fn gen_c_to_rust_bindings(in_file: &str, out_file: &str) {
        println!("cargo:rerun-if-changed={in_file}");

        let allow_types = ["tm", "jmp_buf"];

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

        builder
            .generate()
            .expect("Unable to generate c->rust bindings")
            .write_to_file(out_file)
            .expect("Couldn't write bindings!");
    }

    gen_c_to_rust_bindings("ctypes.h", "src/libctypes_gen.rs");
}
