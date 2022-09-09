fn main() {
    println!("cargo:rustc-link-search=target");
    println!("cargo:rustc-link-lib=app");
}
