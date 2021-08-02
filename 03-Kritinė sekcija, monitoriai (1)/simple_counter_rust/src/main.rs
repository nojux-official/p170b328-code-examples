use std::sync::{Mutex, Condvar, Arc};
use std::thread::JoinHandle;
use std::thread;


const MIN: i32 = 0;
const MAX: i32 = 50;

fn main() {
    // create a mutex that will hold our counter. Initial value is 0. Mutex must be wrapped in
    // atomically counter reference (Arc) because it is used in a thread and Rust cannot tell when
    // it should be destroyed in advance, so it will apply reference counting.
    let mutex = Arc::new(Mutex::new(0));
    // create a conditional variable that will be used to synchronize threads
    let conditional_variable = Arc::new(Condvar::new());
    // a vector that will hold thread join handles
    let mut join_handles: Vec<JoinHandle<_>> = vec![];
    // create 10 threads that will each call increase
    for _ in 0..10 {
        let mutex = Arc::clone(&mutex);
        let conditional_variable = Arc::clone(&conditional_variable);
        let handle = thread::spawn(move || increase(mutex, conditional_variable));
        join_handles.push(handle);
    }
    // create 10 threads that will each call decrease
    for _ in 0..9 {
        // Rust required calling Arc::clone on our references because of safe memory management:
        // when Arc is created, its reference count is 1. When main finishes, our threads might be
        // running (compiler cannot tell if threads will be finished before main finishes), and the
        // end of main will reduce the count. If thread is still running, mutex would be destroyed
        // while still in use by a thread. clone increases the count by one, and the count is
        // decreased at the end of function that uses it. Since we transfer its ownership to a
        // thread, the end of a thread function reduces the count. This way compiler is satisfied
        // and the program is guaranteed to not destroy the mutex too early.
        let mutex = Arc::clone(&mutex);
        let conditional_variable = Arc::clone(&conditional_variable);
        // launch a thread
        let handle = thread::spawn(move || decrease(mutex, conditional_variable));
        join_handles.push(handle);
    }
    // wait for threads to finish
    join_handles.into_iter().for_each(|handle| handle.join().unwrap());
    // retrieve our value
    println!("{}", mutex.lock().unwrap());
}

fn decrease(mutex: Arc<Mutex<i32>>, conditional_variable: Arc<Condvar>) {
    for _ in 0..50 {
        // blocks current thread until *counter <= MIN is false, i.e., if counter <= MIN, thread is
        // blocked
        let mut guard = conditional_variable.wait_while(
            mutex.lock().unwrap(),
            |counter| *counter <= MIN
        ).unwrap();
        // value is guaranteed to be more than MIN, safely decrease it
        *guard -= 1;
        // notify sleeping threads that they should re-check their condition
        conditional_variable.notify_all();
    }
}

fn increase(mutex: Arc<Mutex<i32>>, conditional_variable: Arc<Condvar>) {
    for _ in 0..50 {
        // blocks current thread until *counter >= MAX is false, i.e., if counter >= MAX, thread is
        // blocked
        let mut guard = conditional_variable.wait_while(
            mutex.lock().unwrap(),
            |counter| *counter >= MAX
        ).unwrap();
        // value is guaranteed to be less than MAX, safely increase it
        *guard += 1;
        // notify sleeping threads that they should re-check their condition
        conditional_variable.notify_all();
    }
}
