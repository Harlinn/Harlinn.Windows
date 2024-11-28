/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

use chrono;
use lerp::Lerp;
use libm;

fn run_test<F>(outer_iteration_count : i32, test_name : &str ,func:F, base_value :f64, increment:f64)
where F: Fn(f64) -> f64
{
    for _k in 0..outer_iteration_count
    {
        let mut accumulated:f64=0.0;
        let mut argument_value:f64=base_value;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            accumulated += func(argument_value);
            argument_value += increment;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("{}: Duration= {} Accumulated={}", test_name, duration, accumulated);
    }
}

fn overhead_test(outer_iteration_count : i32)
{
    let test_name = "OverheadTest";
    let test_expression = |x| x;
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn isnan_test(outer_iteration_count : i32)
{
    let test_name = "IsNaNTest";
    let test_expression = |x:f64| if x.is_nan(){1.0}else{0.0};
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn isinf_test(outer_iteration_count : i32)
{
    let test_name = "IsInfTest";
    let test_expression = |x:f64| if x.is_infinite(){1.0}else{0.0};
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn abs_test(outer_iteration_count : i32)
{
    let test_name = "AbsTest";
    let test_expression = |x:f64| x.abs();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn signbit_test(outer_iteration_count : i32)
{
    let test_name = "SignBitTest";
    let test_expression = |x:f64| if x.is_sign_negative() { return 1.0;} else {return 0.0;};
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn frexp_test(outer_iteration_count : i32)
{
    let test_name = "FRexpTest";
    let base_value :f64 = std::f64::consts::PI; 
    let increment:f64 = 0.000001;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated1:f64=0.0;
        let mut accumulated2:f64=0.0;
        let mut argument_value:f64=base_value;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            let result = libm::frexp(argument_value);
            accumulated1 += result.0;
            accumulated2 += f64::from( result.1 );
            argument_value += increment;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("{}: Duration= {} Accumulated 1={} Accumulated 2={}", test_name, duration, accumulated1,accumulated2);
    }
}

fn modf_test(outer_iteration_count : i32)
{
    let test_name = "ModFTest";
    let base_value :f64 = std::f64::consts::PI; 
    let increment:f64 = 0.000001;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated1:f64=0.0;
        let mut accumulated2:f64=0.0;
        let mut argument_value:f64=base_value;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            let result = libm::modf(argument_value);
            accumulated1 += result.0;
            accumulated2 += result.1;
            argument_value += increment;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("{}: Duration= {} Accumulated 1={} Accumulated 2={}", test_name, duration, accumulated1,accumulated2);
    }
}



fn min(first:f64,second:f64) -> f64
{
    if first < second
    {
        return first;
    }
    else
    {
        return second;        
    }
}

fn min_test(outer_iteration_count : i32)
{
    let test_name = "MinTest";
    let test_expression = |x:f64| min(x,x);
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn max(first:f64,second:f64) -> f64
{
    if first > second
    {
        return first;
    }
    else
    {
        return second;        
    }
}

fn max_test(outer_iteration_count : i32)
{
    let test_name = "MaxTest";
    let test_expression = |x:f64| max(x,x);
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn floor_test(outer_iteration_count : i32)
{
    let test_name = "FloorTest";
    let test_expression = |x:f64| x.floor();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn ceil_test(outer_iteration_count : i32)
{
    let test_name = "CeilTest";
    let test_expression = |x:f64| x.ceil();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn trunc_test(outer_iteration_count : i32)
{
    let test_name = "TruncTest";
    let test_expression = |x:f64| x.trunc();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn round_test(outer_iteration_count : i32)
{
    let test_name = "RoundTest";
    let test_expression = |x:f64| x.round();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn clamp_test(outer_iteration_count : i32)
{
    let base_min = std::f64::consts::PI/2.0;
    let base_max = 2.0 * std::f64::consts::PI;
    let base_value = std::f64::consts::PI;
    let increment = 0.000001;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated:f64=0.0;
        let mut argument_value:f64=base_value;
        let mut argument_min = base_min;
        let mut argument_max = base_max;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            accumulated += argument_value.clamp(argument_min, argument_max);
            argument_value += increment;
            argument_min += increment;
            argument_max += increment;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("ClampTest: Duration= {} Accumulated={}", duration, accumulated);
    }
}

fn lerp_test(outer_iteration_count : i32)
{
    let base_min = std::f64::consts::PI/2.0;
    let base_max = 2.0 * std::f64::consts::PI;
    let increment = 0.000001;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated:f64=0.0;
        let mut argument_min = base_min;
        let mut argument_max = base_max;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            accumulated += argument_min.lerp(argument_max,0.5);
            argument_min += increment;
            argument_max += increment;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("LerpTest: Duration= {} Accumulated={}", duration, accumulated);
    }
}

fn copysign_test(outer_iteration_count : i32)
{
    let test_name = "CopySignTest";
    let test_expression = |x:f64| x.copysign(-1.0);
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn scalebn_test(outer_iteration_count : i32)
{
    let value_iteration_count:i64 = 10_000_000;
    let exp_iteration_count:i32 = 100;
    let base_value = std::f64::consts::PI / 2.0;
    let increment = 0.000001;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated:f64=0.0;
        let mut value = base_value;
        let start_time = chrono::Utc::now();
        for _i in 0..value_iteration_count
        {
            for j in 0..exp_iteration_count
            {
                accumulated += libm::scalbn(value, j+1);
            }
            value += increment;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("ScaleBNTest: Duration= {} Accumulated={}", duration, accumulated);
    }
}


fn sin_test(outer_iteration_count : i32)
{
    let test_name = "SinTest";
    let test_expression = |x:f64| x.sin();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI/100.0,0.000001);
}
fn asin_test(outer_iteration_count : i32)
{
    let test_name = "ASinTest";
    let test_expression = |x:f64| x.asin();
    run_test(outer_iteration_count,test_name,test_expression,0.9/1000000000.0, 1.0/1000000000.0);
}

fn cos_test(outer_iteration_count : i32)
{
    let test_name = "CosTest";
    let test_expression = |x:f64| x.cos();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI/100.0,0.000001);
}
fn acos_test(outer_iteration_count : i32)
{
    let test_name = "ACosTest";
    let test_expression = |x:f64| x.acos();
    run_test(outer_iteration_count,test_name,test_expression,0.9/1000000000.0, 1.0/1000000000.0);
}

fn tan_test(outer_iteration_count : i32)
{
    let test_name = "TanTest";
    let test_expression = |x:f64| x.tan();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI/100.0,0.000001);
}
fn atan_test(outer_iteration_count : i32)
{
    let test_name = "ATanTest";
    let test_expression = |x:f64| x.atan();
    run_test(outer_iteration_count,test_name,test_expression,0.9/1000000000.0, 1.0/1000000000.0);
}

fn atan2_test(outer_iteration_count : i32)
{
    let test_name = "ATan2Test";
    let test_expression = |x:f64| x.atan2(x);
    run_test(outer_iteration_count,test_name,test_expression,0.9/1000000000.0, 1.0/1000000000.0);
}

fn sqrt_test(outer_iteration_count : i32)
{
    let test_name = "SqrtTest";
    let test_expression = |x:f64| x.sqrt();
    run_test(outer_iteration_count,test_name,test_expression,std::f64::consts::PI,0.000001);
}

fn nextup_test(outer_iteration_count : i32)
{
    let base_value = 0.0;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated:f64=0.0;
        let mut argument = base_value;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            argument = libm::nextafter(argument,f64::INFINITY);
            accumulated += argument;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("NextUpTest: Duration= {} Accumulated={}", duration, accumulated);
    }
}

fn nextdown_test(outer_iteration_count : i32)
{
    let base_value = 0.0;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated:f64=0.0;
        let mut argument = base_value;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            argument = libm::nextafter(argument,-f64::INFINITY);
            accumulated += argument;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("NextUpTest: Duration= {} Accumulated={}", duration, accumulated);
    }
}

fn fmod_test(outer_iteration_count : i32)
{
    let base_value1:f64 = std::f64::consts::PI;
    let base_value2:f64 = std::f64::consts::PI/4.0;
    let increment:f64 = 0.000001;
    for _k in 0..outer_iteration_count
    {
        let mut accumulated:f64=0.0;
        let mut argument1 = base_value1;
        let mut argument2 = base_value2;
        let inner_iteration_count : i64 = 1000000000;
        let start_time = chrono::Utc::now();
        for _j in 0..inner_iteration_count
        {
            accumulated +=libm::fmod(argument1,argument2);
            argument1 += increment;
            argument2 += increment;
        }
        let end_time = chrono::Utc::now();
        let duration = end_time - start_time;
        
        println!("FModTest: Duration= {} Accumulated={}", duration, accumulated);
    }
}

fn exp_test(outer_iteration_count : i32)
{
    let test_name = "ExpTest";
    let test_expression = |x:f64| x.exp();
    run_test(outer_iteration_count,test_name,test_expression,0.9, 0.000000001);
}

fn hypot_test(outer_iteration_count : i32)
{
    let test_name = "HypotTest";
    let test_expression = |x:f64| x.hypot(x);
    run_test(outer_iteration_count,test_name,test_expression,0.999, 0.000000001);
}

fn log_test(outer_iteration_count : i32)
{
    let test_name = "LogTest";
    let test_expression = |x:f64| x.ln();
    run_test(outer_iteration_count,test_name,test_expression,0.9, 0.000000001);
}

fn log2_test(outer_iteration_count : i32)
{
    let test_name = "Log2Test";
    let test_expression = |x:f64| x.log2();
    run_test(outer_iteration_count,test_name,test_expression,0.9, 0.000000001);
}

fn log10_test(outer_iteration_count : i32)
{
    let test_name = "Log10Test";
    let test_expression = |x:f64| x.log10();
    run_test(outer_iteration_count,test_name,test_expression,0.9, 0.000000001);
}


fn main() 
{
    let outer_iteration_count:i32=1;
    
    overhead_test(outer_iteration_count);
    isnan_test(outer_iteration_count);
    isinf_test(outer_iteration_count);
    abs_test(outer_iteration_count);
    signbit_test(outer_iteration_count);
    frexp_test(outer_iteration_count);
    modf_test(outer_iteration_count);
    min_test(outer_iteration_count);
    max_test(outer_iteration_count);
    floor_test(outer_iteration_count);
    ceil_test(outer_iteration_count);
    trunc_test(outer_iteration_count);
    round_test(outer_iteration_count);
    clamp_test(outer_iteration_count);
    lerp_test(outer_iteration_count);
    copysign_test(outer_iteration_count);
    scalebn_test(outer_iteration_count);
    sin_test(outer_iteration_count);
    asin_test(outer_iteration_count);
    cos_test(outer_iteration_count);
    acos_test(outer_iteration_count);
    tan_test(outer_iteration_count);
    atan_test(outer_iteration_count);
    atan2_test(outer_iteration_count);
    sqrt_test(outer_iteration_count);
    nextup_test(outer_iteration_count);
    nextdown_test(outer_iteration_count);
    fmod_test(outer_iteration_count);
    exp_test(outer_iteration_count);
    hypot_test(outer_iteration_count);
    log_test(outer_iteration_count);
    log2_test(outer_iteration_count);
    log10_test(outer_iteration_count);

    println!("Done!");
}
