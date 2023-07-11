use core::{ffi::c_double, intrinsics};

/// `pow` implementation
#[no_mangle]
pub unsafe extern "C" fn ax_pow(x: c_double, y: c_double) -> c_double {
    info!("ax_pow <= x: {}, y: {}", x, y);
    // intrinsics::powf64(x, y)
    0.0
}

/// `log` implementation
#[no_mangle]
pub unsafe extern "C" fn ax_log(x: c_double) -> c_double {
    // let x_:i64 = core::mem::transmute(x);
    // info!("AX_LOG <= x_: {:064b},", x_);
    let num3 = x;
    info!("ax_log <= x: {}", num3);
    intrinsics::logf64(x)
    // 0.0
}
