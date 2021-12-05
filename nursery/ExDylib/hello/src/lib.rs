#[no_mangle]
pub extern "C" fn my_plus2(x: i32, y: i32) -> i32 {
    x + y
}

#[no_mangle]
pub extern "C" fn my_hello() {
    println!("Hello from Rust.");
}
