use milone_sys::MString;
use std::fs;

mod milone_sys {
    use std::marker::PhantomData;

    #[repr(C)]
    pub struct MString {
        ptr: *mut u8,
        len: u32,
    }

    pub struct Borrow<'a, T> {
        pub value: T,
        _phantom: PhantomData<&'a T>,
    }

    impl MString {
        pub fn from_str(s: &str) -> Borrow<MString> {
            let value = MString {
                ptr: s.as_ptr() as *mut u8,
                len: s.len() as u32,
            };
            Borrow {
                value,
                _phantom: PhantomData,
            }
        }

        pub unsafe fn as_str(&self) -> &'static str {
            if self.len == 0 {
                return "";
            }

            let v = std::slice::from_raw_parts(self.ptr as *const u8, self.len as usize);
            std::str::from_utf8(v).unwrap()
        }
    }
}

#[link(name = "app")]
extern "C" {
    fn AppBlog_initialize();
    fn generate(contents: milone_sys::MString) -> milone_sys::MString;
}

fn main() {
    unsafe { AppBlog_initialize() };

    fs::create_dir_all("target/pages").unwrap();

    for entry in fs::read_dir("data/pages").unwrap() {
        let path = entry.unwrap().path();
        let name = path.file_stem().unwrap().to_str().unwrap();
        let contents = {
            let path = path.to_str().unwrap();
            fs::read_to_string(&path).unwrap()
        };
        let output = format!("target/pages/{name}.html");

        {
            let contents = MString::from_str(&contents);
            let html = unsafe { generate(contents.value) };
            let html = unsafe { html.as_str() };

            eprintln!("writing {output}");
            fs::write(output, html).unwrap();
        }
    }
}
